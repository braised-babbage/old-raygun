#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
public:
  ray() {}
  ray(const vec3& o, const vec3& v) : o(o), v(v) {}
  vec3 origin() const { return o; }
  vec3 direction() const { return v; }
  vec3 point_at_parameter(float t) const { return o + t*v; }

  vec3 o;
  vec3 v;
};
  
#endif
