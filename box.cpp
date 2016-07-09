#include <memory>
#include <vector>
#include "box.h"
#include "rect.h"


using std::shared_ptr;
using std::make_shared;

box::box(const vec3& p0, const vec3& p1, shared_ptr<material> mat) {
  pmin = p0;
  pmax = p1;
  std::vector<shared_ptr<hitable> > objects;
  objects.push_back(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(),
					 p1.z(), mat));
  objects.push_back(make_shared<flipped_normals>(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), mat)));
  objects.push_back(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(),
					 p1.y(), mat));
  objects.push_back(make_shared<flipped_normals>(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), mat)));
  objects.push_back(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(),
					 p1.x(), mat));
  objects.push_back(make_shared<flipped_normals>(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.z(), mat)));
  
  walls = make_shared<bvh_node>(objects.begin(), objects.end(), 0.0, 1.0);
}

bool box::hit(const ray& r, float t0, float t1, hit_record& rec) const {
  return walls->hit(r,t0,t1,rec);
}

bool box::bounding_box(float t0, float t1, aabb& box) const {
  box = aabb(pmin, pmax);
  return true;
}
