#ifndef MATERIALH
#define MATERIALH
#include "util.h"
#include "hitable.h"


class material {
public:
  virtual bool scatter(const ray& r_in, const hit_record& rec,
		       vec3& attenuation, ray& scattered)  = 0;
};

class lambertian : public material {
public:
  lambertian(const vec3& albedo) : albedo(albedo) {}

  virtual bool scatter(const ray& r, const hit_record& rec,
		       vec3& attenuation, ray& scattered) {

    vec3 target = rec.p + rec.normal + random_in_unit_ball();
    scattered = ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
  }
  
  vec3 albedo;
};

vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2*dot(v,n)*n;
}

class metal : public material {
public:
  metal(const vec3& albedo) : albedo(albedo) {}

  virtual bool scatter(const ray& r, const hit_record& rec,
		       vec3& attenuation, ray& scattered) {
    vec3 reflected = reflect(r.direction(), rec.normal);
    scattered = ray(rec.p,reflected);
    attenuation = albedo;
    return dot(scattered.direction(),rec.normal) > 0;
  }

  vec3 albedo;
};

#endif
