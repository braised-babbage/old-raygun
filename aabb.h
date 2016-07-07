#ifndef AABBH
#define AABBH

#include "vec3.h"
#include "ray.h"

class aabb {
public:
  aabb() { }
  aabb(const vec3& a, const vec3& b) { _min = a; _max = b; }

  vec3 min() const { return _min; }
  vec3 max() const { return _max; }

  inline bool hit(const ray& r, float tmin, float tmax) const;
  
private:
  vec3 _min;
  vec3 _max;
  
};

inline bool aabb::hit(const ray& r, float tmin, float tmax) const {
  for (int i = 0; i < 3; i++) {
    float invD = 1.0f / r.direction()[i];
    float t0 = (min()[i] - r.origin()[i]) * invD;
    float t1 = (max()[i] - r.origin()[i]) * invD;
    if (invD < 0.0f)
      std::swap(t0, t1);
    tmin = t0 > tmin ? t0 : tmin;
    tmax = t1 < tmax ? t1 : tmax;
    if (tmax <= tmin)
      return false;
  }
  return true;
}


#endif
