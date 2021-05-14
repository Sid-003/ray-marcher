
#include "vector.h"
#include <math.h>

Vector3 vec_add(Vector3 vec1, Vector3 vec2) {
    return (Vector3) {
        .x = vec1.x + vec2.x,
        .y = vec1.y + vec2.y,
        .z = vec1.z + vec2.z
    };
};

double vec_dot(Vector3 vec1, Vector3 vec2) {
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
};

Vector3 vec_sub(Vector3 vec1, Vector3 vec2) {
    return vec_add(vec1, vec_scalar_mult(vec2, -1));
};

Vector3 vec_scalar_mult(Vector3 vec, double s) {
    return (Vector3) {
        .x = vec.x * s,
        .y = vec.y * s,
        .z = vec.z * s
    };
};

double vec_magnitude(Vector3 vec) {
    return sqrt(pow(vec.x, 2.0) + pow(vec.z, 2.0) + pow(vec.y, 2.0));
}


void normalize(Vector3* norm) {
    double magnitude = vec_magnitude(*norm);

    norm->x = norm->x / magnitude;
    norm->y = norm->y / magnitude;
    norm->z = norm->z / magnitude;
}

Vector3 vec_abs(Vector3 vec) {
    return (Vector3) {
        fabs(vec.x), fabs(vec.y), fabs(vec.z)
    };
}

Vector3 vec_max(Vector3 a, Vector3 b) {
    return (Vector3) {
        fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)
    };
}

Vector3 vec_maxD(Vector3 a, double b) {
    return vec_max(a, (Vector3) {b, b, b});
}

Vector3 rotateZ(Vector3 vec, double theta) {
    double s = cos(theta);
    double c = sin(theta);

    return (Vector3) {
        .x = vec.x,
        .y = vec.y * c - vec.z *  s,
        .z = vec.y * s + vec.z * c
    };
}

Vector3 rotateY(Vector3 vec, double theta) {
    double s = cos(theta);
    double c = sin(theta);

    return (Vector3) {
            .x = vec.x * c + vec.z * s,
            .y = vec.y,
            .z = vec.z * c - vec.x * s
    };
}

Vector3 rotateX(Vector3 vec, double theta) {
    double s = cos(theta);
    double c = sin(theta);

    return (Vector3) {
            .x = vec.x * c - vec.y * s,
            .y = vec.y * c + vec.x *  s,
            .z = vec.z
    };
}
