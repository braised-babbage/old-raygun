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

class moving_sphere : public hitable {
public:
  moving_sphere() {}
  moving_sphere(vec3 center0, vec3 center1, float t0, float t1, float r, material* mat) :
    center0(center0), center1(center1), time0(t0), time1(t1), radius(r), mat(mat) {};
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record &rec) const;
  bool bounding_box(float t0, float t1, aabb& box) const;
  vec3 center(float time) const;
private:
  vec3 center0, center1;
  float time0, time1;
  float radius;
  material *mat;
};

vec3 moving_sphere::center(float time) const{
  return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}

bool moving_sphere::hit(const ray& ray, float t_min, float t_max, hit_record &rec) const
{
  vec3 sc = center(ray.time());
  vec3 oc = ray.origin() - sc;
  float a = dot(ray.direction(), ray.direction());
  float b = 2.0 * dot(oc, ray.direction());
  float c = dot(oc, oc) - (radius)*(radius);
  float discriminant = b*b - 4*a*c;
  if (discriminant >= 0) {
    float t = (-b - sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = (rec.p - sc)/radius;
      rec.mat = mat;
      return true;
    }
    t = (-b + sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = (rec.p - sc)/radius;
      rec.mat = mat;
      return true;
    }
  }
  return false;
}

bool moving_sphere::bounding_box(float t0, float t1, aabb& box) const {

  vec3 c0 = center(t0);
  vec3 c1 = center(t1);
  vec3 rvec = vec3(radius, radius, radius);

  box = surrounding_box(aabb(c0 - rvec, c0 + rvec),
			aabb(c1 - rvec, c1 + rvec));
  return true;
}

#endif
