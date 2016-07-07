#ifndef SPHEREH
#define SPHEREH
#include "vec3.h"
#include "hitable.h"
#include "material.h"
#include "aabb.h"

class sphere : public hitable {
public:
  sphere(vec3 center, float radius, material* mat)
    : center(center), radius(radius), mat(mat)
  {}

  virtual bool hit(const ray& ray, float t_min, float t_max, hit_record &rec) const;

  virtual bool bounding_box(float t0, float t1, aabb& box) const;

private:
  vec3 center;
  float radius;
  material* mat;
};

bool sphere::hit(const ray& ray, float t_min, float t_max, hit_record &rec) const
{
  vec3 oc = ray.origin() - center;
  float a = dot(ray.direction(), ray.direction());
  float b = 2.0 * dot(oc, ray.direction());
  float c = dot(oc, oc) - (radius)*(radius);
  float discriminant = b*b - 4*a*c;
  if (discriminant >= 0) {
    float t = (-b - sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = (rec.p - center)/radius;
      rec.mat = mat;
      return true;
    }
    t = (-b + sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = (rec.p - center)/radius;
      rec.mat = mat;
      return true;
    }
  }
  return false;
}

bool sphere::bounding_box(float t0, float t1, aabb& box) const
{
  box = aabb(center - vec3(radius, radius, radius),
	     center + vec3(radius, radius, radius));
  return true;
}

#endif
