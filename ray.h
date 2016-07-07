#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
public:
  ray() {}
  ray(const vec3& o, const vec3& v, float t = 0.0) : o(o), v(v), t(t) {}
  vec3 origin() const { return o; }
  vec3 direction() const { return v; }
  float time() const { return t; }
  vec3 point_at_parameter(float t) const { return o + t*v; }
private:
  vec3 o;
  vec3 v;
  float t;
};
  
#endif
