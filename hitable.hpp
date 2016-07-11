#ifndef HITABLEH
#define HITABLEH

#include <memory>
#include "vec3.hpp"
#include "ray.hpp"
#include "aabb.hpp"

class material;

struct hit_record
{
  float t;
  vec3 p;
  vec3 normal;
  float u, v;
  std::shared_ptr<material> mat;
};

class hitable
{
public:
  virtual bool hit(const ray& ray, float t_min, float t_max, hit_record &rec) const = 0;
  virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};

class flipped_normals : public hitable {
public:
  flipped_normals(std::shared_ptr<hitable> h) : h(h) {}
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record &rec) const {
    if (h->hit(r, tmin, tmax, rec)) {
      rec.normal = -rec.normal;
      return true;
    }
    else
      return false;
  }
  virtual bool bounding_box(float t0, float t1, aabb& box) const {
    return h->bounding_box(t0, t1, box);
  }
private:
  std::shared_ptr<hitable> h;
};

#endif
