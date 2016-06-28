#ifndef UTILH
#define UTILH

#include <cstdlib>
#include <limits>
#include "vec3.h"

const float FLOAT_MAX = std::numeric_limits<float>::max();

vec3 linear_interpolate(const vec3 &v1, const vec3 &v2, float t);

double rz1();

vec3 random_in_unit_ball();

vec3 random_in_unit_disk();

#endif
