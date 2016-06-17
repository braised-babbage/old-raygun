#ifndef HITABLEH
#define HITABLEH
#include "vec3.h"

struct hit_record
{
  float t;
  vec3 p;
  vec3 normal;
};

class hitable
{
  virtual bool hit(const ray& ray, float t_min, float t_max, hit_record &rec) = 0;
};

#endif