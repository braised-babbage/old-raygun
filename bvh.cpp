#include <algorithm>
#include <iterator>
#include "bvh.h"
#include "util.h"

bool bvh_node::bounding_box(float t0, float t1, aabb& b) const {
  b = box;
  return true;
}

bool bvh_node::hit(const ray& r, float tmin, float tmax, hit_record& rec) {
  if (box.hit(r, tmin, tmax)) {
    hit_record left_rec, right_rec;
    bool hit_left = left->hit(r, tmin, tmax, left_rec);
    bool hit_right = right->hit(r, tmin, tmax, right_rec);

    if (hit_left && hit_right) {
      rec = left_rec.t < right_rec.t ? left_rec : right_rec;
      return true;
    }
    else if (hit_left) {
      rec = left_rec;
      return true;
    }
    else if (hit_right) {
      rec = right_rec;
      return true;
    }
  }
  return false;
}



bool compare_y(std::shared_ptr<hitable> a, std::shared_ptr<hitable> b)
{
  aabb box_left, box_right;
  if (!a->bounding_box(0,0, box_left) || !b->bounding_box(0,0, box_right))
    std::cerr << "no bounding box in bvh_node constructor" << std::endl;
  
  return box_left.min()[1] < box_right.min()[1];
}


bool compare_z(std::shared_ptr<hitable> a, std::shared_ptr<hitable> b)
{
  aabb box_left, box_right;
  if (!a->bounding_box(0,0, box_left) || !b->bounding_box(0,0, box_right))
    std::cerr << "no bounding box in bvh_node constructor" << std::endl;
  
  return box_left.min()[2] < box_right.min()[2];
}

bvh_node::bvh_node(vec_iter start, vec_iter end, float t0, float t1) {
  int axis = int(3*rz1());

  auto compare_fn = [&](std::shared_ptr<hitable> a,
			std::shared_ptr<hitable> b) {
    aabb box_left, box_right;
    if (!a->bounding_box(0,0, box_left) || !b->bounding_box(0,0, box_right))
      std::cerr << "no bounding box in bvh_node constructor" << std::endl;
    
    return box_left.min()[axis] < box_right.min()[axis];
  };
  
  std::sort(start, end, compare_fn);
  int n = std::distance(start, end);
  if (n <= 2) {
    left = *start;
    right = *(end-1);
  }
  else {
    left = std::shared_ptr<hitable>(new bvh_node(start, start + n/2, t0, t1));
    right = std::shared_ptr<hitable>(new bvh_node(start + n/2, end, t0, t1));
  }
  aabb box_left, box_right;
  if (!left->bounding_box(t0, t1, box_left) || !right->bounding_box(t0,t1, box_right))
    std::cerr << "no bounding box in bvh_node constructor" << std::endl;
  box = surrounding_box(box_left, box_right);
}

