#pragma once
#include "vector.h"

typedef struct {
    Vector3 color;
    double distance;
} SDFResult;

typedef SDFResult (*DE)(Vector3);

SDFResult among_gus(Vector3 pos);
