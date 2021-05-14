#include <math.h>
#include "sdfs.h"

Vector3 repeat_xyz(Vector3 pos, double fx, double fy, double fz) {
    pos.x = fmod(pos.x + 0.5 * fx, fx) - 0.5 * fx;
    pos.y = fmod(pos.y + 0.5 * fy, fy) - 0.5 * fy;
    pos.z = fmod(pos.z + 0.5 * fz, fz) - 0.5 * fz;

    return pos;
}

Vector3 repeat_xz(Vector3 pos, double fx, double fz) {
    pos.x = fmod(pos.x + 0.5 * fx, fx) - 0.5 * fx;
    pos.z = fmod(pos.z + 0.5 * fz, fz) - 0.5 * fz;

    return pos;
}

//stolen from: //stolen from: http://blog.hvidtfeldts.net/index.php/2011/09/distance-estimated-3d-fractals-v-the-mandelbulb-different-de-approximations/
SDFResult mandelbulb(Vector3 pos) {
    double power = 8.0;

    Vector3 z = pos;

    double dr = 1.0;
    double r = 0.0;

    for (int i = 0; i < 10; i++) {
        r = vec_magnitude(z);

        if (r > 2.0)
            break;

        double theta = acos(z.z / r);
        double phi = atan(z.y / z.x);
        dr = pow(r, power - 1.0) * power * dr + 1.0;

        double zr = pow(r, power);
        theta *= power;
        phi *= power;

        z = vec_add(vec_scalar_mult((Vector3) {sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta)}, zr), pos);
    }

    return (SDFResult) {
        .distance = 0.5 * log(r) * r/dr,
        .color = (Vector3){1.0, 1.0, 1.0}
    };
}

SDFResult distance_sphere(Vector3 pos, Vector3 sPos, double radius, double displacement) {
    return (SDFResult) { .distance = vec_magnitude(vec_sub(pos, sPos)) - radius + displacement,
                         .color =  {1.0, 0, 0}};
}

SDFResult distance_box(Vector3 p, Vector3 boxPos, Vector3 b, double r)
{
    p = vec_sub(p, boxPos);
    Vector3 q = vec_sub(vec_abs(p), b);
    double distance = vec_magnitude(vec_maxD(q,0.0)) + fmin(fmax(q.x,fmax(q.y,q.z)),0.0) - r;

    return (SDFResult) {
        .distance = distance,
        .color = (Vector3) {.z = 1.0}
    };
}

double clamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}

SDFResult distance_capsule(Vector3 pos, Vector3 cPos, double h, double r )
{
    double displacement = sin(5.0 * pos.x) * sin(5.0 * pos.y) * sin(5.0 * pos.z) * 0.25;
    pos.y -= clamp(pos.y, 0.0, h);
    return (SDFResult) {.distance = vec_magnitude(vec_sub(pos, cPos)) - r + displacement,
                        .color = {0, 1.0, 0}};
}

SDFResult sdf_union(SDFResult a, SDFResult b) {
    if (a.distance < b.distance) {
        return a;
    }

    return b;
}

SDFResult sdf_intersect(SDFResult a, SDFResult b) {
    if (a.distance > b.distance) {
        return a;
    }
    return b;
}

SDFResult scene(Vector3 pos) {
    return mandelbulb(pos);
}
