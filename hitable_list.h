#ifndef HITABLE_LISTH
#define HITABLE_LISTH

#include <vector>
#include <memory>
#include "vec3.h"
#include "hitable.h"


class hitable_list : public hitable
{
public:
  hitable_list() {}
  // hitable_list(hitable **l, int n) {list = l; list_size = n; }
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const;
  
  void add(std::shared_ptr<hitable> item)
  {
    list.push_back(item);
  }
private:
  typedef std::shared_ptr<hitable> hit_sp;
  std::vector<hit_sp> list;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;

  for (std::vector<hit_sp>::const_iterator iter = list.begin();
       iter != list.end(); ++iter) {
    if ((*iter)->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }
  return hit_anything;
}

bool hitable_list::bounding_box(float t0, float t1, aabb& box) const
{
  return false; // TODO: implement this
}


#endif
