#include <cmath>
#include "sphere.h"
#include "vec3.h"
#include "ray.h"

// spherical coordinates, normalized to [0,1]
void get_sphere_uv(const vec3& p, float& u, float& v) {
  float phi = atan2(p.z(), p.x());
  float theta = asin(p.y());
  u = 1 - (phi + M_PI) / (2*M_PI);
  v = (theta + M_PI/2) / M_PI;
}

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
      get_sphere_uv((rec.p - center), rec.u, rec.v);
      return true;
    }
    t = (-b + sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = (rec.p - center)/radius;
      rec.mat = mat;
      get_sphere_uv((rec.p - center), rec.u, rec.v);
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
      get_sphere_uv((rec.p - sc), rec.u, rec.v);
      return true;
    }
    t = (-b + sqrt(discriminant) ) / (2.0*a);
    if (t > t_min && t < t_max) {
      rec.t = t;
      rec.p = ray.point_at_parameter(t);
      rec.normal = (rec.p - sc)/radius;
      rec.mat = mat;
      get_sphere_uv((rec.p - sc), rec.u, rec.v);
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
