#ifndef MATERIALH
#define MATERIALH

#include <cmath>
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
		       vec3& attenuation, ray& scattered);
private:  
  vec3 albedo;
};


class metal : public material {
public:
  metal(const vec3& albedo, float f) : albedo(albedo)
  {
    fuzz = (f < 1) ? f : 1;
  }

  virtual bool scatter(const ray& r, const hit_record& rec,
		       vec3& attenuation, ray& scattered);
private:
  vec3 albedo;
  float fuzz;
};

class dialectric : public material {
public:
  dialectric(float ri) : ri(ri) {}

  virtual bool scatter(const ray& r, const hit_record& rec,
		       vec3& attenuation, ray& scattered);
private:
  float ri;
};

#endif
