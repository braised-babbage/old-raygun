#ifndef RECTH
#define RECTH

#include <memory>
#include "hitable.h"

const float BB_TOL = 0.0001;

class xy_rect : public hitable {
public:
  xy_rect() {}
  xy_rect(float x0, float x1, float y0, float y1, float k,
	  std::shared_ptr<material> mat) :
    x0(x0), x1(x1), y0(y0), y1(y1), k(k), mat(mat) {}
  virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const {
    box = aabb(vec3(x0, y0, k - BB_TOL), vec3(x1,y1,k+BB_TOL));
    return true;
  }
private:
  float x0, x1, y0, y1, k;
  std::shared_ptr<material> mat;
};

#endif
