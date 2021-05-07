#pragma once

#include "vector.h"
#include "sdfs.h"

typedef struct {
    double distance, steps, totalDistance;
    Vector3 color;
} Hit;

Vector3 get_color(Vector3 origin, Vector3 dir, DE f);