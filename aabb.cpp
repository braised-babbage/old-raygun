#include <algorithm>
#include "aabb.h"

inline bool aabb::hit(const ray& r) const {
  for (int i = 0; i < 3; i++) {
    float invD = 1.0f / r.direction()[i];
    float t0 = (min()[i] - r.origin()[i]) * invD;
    float t1 = (max()[i] - r.origin()[i]) * invD;
    if (invD < 0.0f)
      std::swap(t0, t1);
    if (t1 <= t0)
      return false;
  }
  return true;
}
	       
