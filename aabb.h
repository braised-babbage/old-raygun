#ifndef AABBH
#define AABBH

#include "vec3.h"
#include "ray.h"

class aabb {
public:
  aabb(const vec3& a, const vec3& b) { _min = a; _max = b; }

  vec3 min() const { return _min; }
  vec3 max() const { return _max; }

  inline bool hit(const ray& r) const;
  
private:
  vec3 _min;
  vec3 _max;
  
};

#endif
