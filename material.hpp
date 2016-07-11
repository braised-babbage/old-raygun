#ifndef MATERIALH
#define MATERIALH

#include <memory>
#include <cmath>
#include "util.hpp"
#include "hitable.hpp"
#include "texture.hpp"


class material {
public:
  virtual bool scatter(const ray& r_in, const hit_record& rec,
		       vec3& attenuation, ray& scattered)  = 0;
  virtual vec3 emitted(float u, float v, const vec3& p) const
  { return vec3(0,0,0); }
};

class lambertian : public material {
public:
  lambertian(std::shared_ptr<texture> albedo) : albedo(albedo) {}

  virtual bool scatter(const ray& r, const hit_record& rec,
		       vec3& attenuation, ray& scattered);
private:  
  std::shared_ptr<texture> albedo;
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

class diffuse_light : public material {
public:
  diffuse_light(std::shared_ptr<texture> emit) : emit(emit) {}
  virtual bool scatter(const ray& r_in, const hit_record& rec,
		       vec3& attenuation, ray& scattered)
  { return false; }
  virtual vec3 emitted(float u, float v, const vec3& p) const
  { return emit->value(u, v, p); }
private:
  std::shared_ptr<texture> emit;
};

#endif
