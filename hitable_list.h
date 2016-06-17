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
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec);

  void add(std::shared_ptr<hitable> item)
  {
    list.push_back(item);
  }
  
  std::vector<std::shared_ptr<hitable> > list;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) {
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;
  for (int i = 0; i < list.size(); i++) {
    if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }
  return hit_anything;
}


#endif
