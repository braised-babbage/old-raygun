#ifndef TRANSFORMH
#define TRANSFORMH

#include "hitable.h"
#include "vec3.h"

class translated : public hitable {
public:
  translated(std::shared_ptr<hitable> h, const vec3& displacement) : h(h), displacement(displacement) {}
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const;
private:
  std::shared_ptr<hitable> h;
  vec3 displacement;
};

class rotated_y : public hitable {
public:
  rotated_y(std::shared_ptr<hitable> h, float angle);
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const {
    box = bbox; return hasbox; }
private:
  std::shared_ptr<hitable> h;
  float sin_theta;
  float cos_theta;
  bool hasbox;
  aabb bbox;
};


#endif
