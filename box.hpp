#ifndef BOXH
#define BOXH

#import <memory>
#import "hitable.hpp"
#import "ray.hpp"
#import "vec3.hpp"
#import "bvh.hpp"
#import "aabb.hpp"

class box : public hitable {
public:
  box() {}
  box(const vec3& p0, const vec3& p1, std::shared_ptr<material> mat);
  virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const;
private:
  vec3 pmin, pmax;
  std::shared_ptr<bvh_node> walls;
};

#endif
