#pragma once

typedef struct {
    double x, y, z;
} Vector3;

Vector3 vec_add(Vector3, Vector3);
Vector3 vec_sub(Vector3, Vector3);
Vector3 vec_scalar_mult(Vector3, double);
Vector3 vec_max(Vector3, Vector3);
Vector3 vec_maxD(Vector3, double);

Vector3 rotateX(Vector3 vec, double theta);
Vector3 rotateY(Vector3 vec, double theta);
Vector3 rotateZ(Vector3 vec, double theta);

double vec_magnitude(Vector3);
double vec_dot(Vector3 vec1, Vector3 vec2);
void normalize(Vector3* norm);
Vector3 vec_abs(Vector3 vec);