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
  metal(const vec3& albedo, float f) : albedo(albedo)
  {
    fuzz = (f < 1) ? f : 1;
  }

  virtual bool scatter(const ray& r, const hit_record& rec,
		       vec3& attenuation, ray& scattered) {
    vec3 reflected = reflect(r.direction(), rec.normal);
    scattered = ray(rec.p,reflected + fuzz*random_in_unit_ball());
    attenuation = albedo;
    return dot(scattered.direction(),rec.normal) > 0;
  }

  vec3 albedo;
  float fuzz;
};

bool refract(const vec3& v, const vec3& n, float r, vec3& refracted) {
  // https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
  vec3 l = unit_vector(v);
  float c = -dot(l, n);
  float discriminant = 1.0 - r*r*(1-c*c);
  if (discriminant > 0) {
    refracted = r*l + (r*c - sqrt(discriminant))*n;
    return true;
  }
  else
    return false;
}

class dialectric : public material {
public:
  dialectric(float ri) : ri(ri) {}
  virtual bool scatter(const ray& r_in, const hit_record& rec,
		       vec3& attenuation, ray& scattered) {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ratio;
    attenuation = vec3(1.0,1.0,1.0);
    vec3 refracted;
    if (dot(r_in.direction(), rec.normal) > 0) {
      outward_normal = -rec.normal;
      ratio = ri; // air has RI of 1
    }
    else {
      outward_normal = rec.normal;
      ratio = 1.0 / ri; // air has RI of 1
    }
    if (refract(r_in.direction(), outward_normal, ratio, refracted)) {
      scattered = ray(rec.p, refracted);
    }
    else {
      scattered = ray(rec.p, reflected);
      return false;
    }
    return true;
  }

  float ri;
};

#endif
