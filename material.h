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

#endif
