#ifndef BVHH
#define BVHH

#include <vector>

#include "hitable.h"
#include "aabb.h"

class bvh_node : public hitable {
public:
  typedef std::vector<std::shared_ptr<hitable> >::iterator vec_iter;
  bvh_node(vec_iter start, vec_iter end, float t0, float t1);
  
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec);
  virtual bool bounding_box(float t0, float t1, aabb& box) const;

private:
  std::shared_ptr<hitable> left, right;
  aabb box;
};

#endif
