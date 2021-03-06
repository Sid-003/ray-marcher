#include "marcher.h"
#include <math.h>

#define MIN_DIST 0.001
#define MAX_DIST 20
#define MAX_STEPS 256
#define SHADOW 0.9

//https://www.iquilezles.org/www/articles/normalsSDF/normalsSDF.htm
Vector3 surface_normal(Vector3 pos, DE f) {
    const double eps = 0.001;

    const Vector3 xyy = {.x = eps};
    const Vector3 yxy = {.y = eps};
    const Vector3 yyx = {.z = eps};

    Vector3 normal = {
            .x = f(vec_add(pos, xyy)).distance - f(vec_sub(pos, xyy)).distance,
            .y = f(vec_add(pos, yxy)).distance - f(vec_sub(pos, yxy)).distance,
            .z = f(vec_add(pos, yyx)).distance - f(vec_sub(pos, yyx)).distance
    };

    normalize(&normal);

    return normal;
}

Hit march(Vector3* origin, Vector3 rayDir, DE estimator) {
    double totalDist = 0;

    double d = 0;
    int steps = 0;

    Hit hit = {};
    for (; steps < MAX_STEPS; steps += 1) {
        SDFResult res = estimator(*origin);

        d = res.distance;

        if (d < MIN_DIST) {
            hit.color = res.color;
            break;
        }

        if (d > MAX_DIST) {
            break;
        }
        *origin = vec_add(*origin, vec_scalar_mult(rayDir, d));
        totalDist += d;
    }

    hit.distance = d;
    hit.steps = (double) steps;
    hit.totalDistance = totalDist;
    return hit;
}

double soft_shadow(Vector3 origin, Vector3 lightDir, DE f, double k) {
    double totalDist = 0.1;
    double res = 1.0;

    for (int steps=0; steps < MAX_STEPS; steps++) {
        double d = f(vec_add(origin, vec_scalar_mult(lightDir, totalDist))).distance;

        if (d < MIN_DIST) {
            return (1.0 - SHADOW);
        }

        if (d > MAX_DIST) {
            break;
        }
        res = fmin(res, k * d / totalDist);
        totalDist += d;
    }

    return res;
}

Vector3 get_color(Vector3 origin, Vector3 dir, DE f) {

    Hit h = march(&origin, dir, f);

    Vector3 col = h.color;
    if (h.distance < MIN_DIST) {
        Vector3 normal = surface_normal(origin, f);

        //alternatively could do lightDir = origin - lightPos
        Vector3  lightDir = {-0.5, 1.0, -0.5};

        normalize(&lightDir);

        //soft-shadow march
        double k = soft_shadow(origin, lightDir, f, 5);

        //diffuse lighting
        k *= fmax(0.0, vec_dot(lightDir, normal));

        col = vec_scalar_mult(col, k);

        return col;
    }
    return (Vector3) {1.0, 1.0, 1.0};
}