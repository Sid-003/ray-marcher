#include <math.h>
#include "sdfs.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

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

SDFResult distance_capsule(Vector3 pos, Vector3 cPos, double h, double r )
{
    double displacement = sin(5.0 * pos.x) * sin(5.0 * pos.y) * sin(5.0 * pos.z) * 0.25;
    pos.y -= CLAMP(pos.y, 0.0, h);
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

SDFResult among_gus(Vector3 pos) {

    //SDFResult  sdfA = distance_sphere(repeat_xz(pos, 2.0, 2, 2.0), (Vector3) {0.0, 2.0, 0.0}, 0.5, 0);
    //sdfA.color = (Vector3){0, 1, 0};

    SDFResult  sdfA = distance_sphere(repeat_xz(pos, 5, 5), (Vector3) {0, 0, 0}, 0.5, 0);
    //SDFResult sdfA = distance_capsule(pos, (Vector3) {}, 1.0, 1.0);
    SDFResult planeFloor = {.distance = pos.y + 0.5, .color = (Vector3) {.x = 0.2, .y = 0.2, .z = 0.2}};
    //SDFResult sdfB = distance_box(pos, (Vector3) {.y = 0.5, .z = 0.7}, (Vector3) {0.5, 0.3, 2.5}, 0.1);
    //sdfB.color = (Vector3) {1, 1, 1};
    return sdf_union(sdfA, planeFloor);
}