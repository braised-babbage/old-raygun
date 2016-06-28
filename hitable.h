#ifndef HITABLEH
#define HITABLEH

#include "vec3.h"
#include "ray.h"

class material;

struct hit_record
{
  float t;
  vec3 p;
  vec3 normal;
  material *mat;
};

class hitable
{
public:
  virtual bool hit(const ray& ray, float t_min, float t_max, hit_record &rec) = 0;
};

#endif
