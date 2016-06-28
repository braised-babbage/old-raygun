#include <cstdlib>
#include <limits>
#include "vec3.h"

vec3 linear_interpolate(const vec3 &v1, const vec3 &v2, float t) {
  return v1*(1.0-t) + v2*t;
}

// TODO : c++ style rng?
double rz1() // random zero to one
{
    return rand() / (RAND_MAX + 1.);
}

vec3 random_in_unit_ball() {
  vec3 p;
  do {
    p = 2.0*vec3(rz1(), rz1(), rz1()) - vec3(1,1,1);
  } while (dot(p,p) >= 1.0);
  return p;
}

vec3 random_in_unit_disk() {
  // random vector in the disc z = 0, x^2 + y^2 <= 1
  vec3 p;
  do {
    p = 2.0*vec3(rz1(), rz1(), 0) - vec3(1,1,0);
  } while (dot(p,p) >= 1.0);
  return p;
}
