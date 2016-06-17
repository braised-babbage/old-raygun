#ifndef SPHEREH
#define SPHEREH
#include "vec3.h"
#include "hitable.h"

class sphere : public hitable {
public:
  sphere(vec3 center, float radius) : center(center), radius(radius) {}

  virtual bool hit(const ray& ray, float t_min, float t_max, hit_record &rec);

  vec3 center;
  float radius;
};

Bool sphere::hit(const ray& ray, float t_min, float t_max, hit_record &rec)
{
  vec3 oc = ray.origin() - this->center;
  float a = dot(ray.direction(), ray.direction());
  float b = 2.0 * dot(oc, ray.direction());
  float c = dot(oc, oc) - (this->radius)*(this->radius);
  float discriminant = b*b - 4*a*c;
  if (discriminant >= 0) {
    float t = (-b - sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = rec.p - ray.origin();
      return true;
    }
    t = (-b + sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = rec.p - ray.origin();
      return true;
    }
  }
  return false;
}

#endif
