#ifndef SPHEREH
#define SPHEREH
#include "vec3.h"
#include "hitable.h"
#include "material.h"
#include "aabb.h"

class sphere : public hitable {
public:
  sphere(vec3 center, float radius, std::shared_ptr<material> mat)
    : center(center), radius(radius), mat(mat)
  {}

  virtual bool hit(const ray& ray, float t_min, float t_max, hit_record &rec) const;

  virtual bool bounding_box(float t0, float t1, aabb& box) const;

private:
  vec3 center;
  float radius;
  std::shared_ptr<material> mat;
};

class moving_sphere : public hitable {
public:
  moving_sphere() {}
  moving_sphere(vec3 center0, vec3 center1, float t0, float t1, float r,
		std::shared_ptr<material> mat) :
    center0(center0), center1(center1), time0(t0), time1(t1), radius(r), mat(mat) {};
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record &rec) const;
  bool bounding_box(float t0, float t1, aabb& box) const;
  vec3 center(float time) const;
private:
  vec3 center0, center1;
  float time0, time1;
  float radius;
  std::shared_ptr<material> mat;
};

#endif
