#pragma once
#include "vector.h"

typedef struct {
    Vector3 color;
    double distance;
} SDFResult;

typedef SDFResult (*DE)(Vector3);

SDFResult scene(Vector3 pos);
