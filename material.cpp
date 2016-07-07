#include <cmath>
#include "material.h"
#include "vec3.h"
#include "util.h"
#include "hitable.h"
#include "texture.h"

vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2*dot(v,n)*n;
}


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

// Reflectivity varies with angle,
// this is a simple polynomial approximation
// TODO : to what?
// for that (by Christophe Schlick)
float schlick(float cosine, float ri) {
  float r0 = (1 - ri) / (1 + ri);
  r0 = r0*r0;
  return r0 + (1-r0)*pow((1-cosine),5);
}



bool lambertian::scatter(const ray& r, const hit_record& rec,
			 vec3& attenuation, ray& scattered) {

  vec3 target = rec.p + rec.normal + random_in_unit_ball();
  scattered = ray(rec.p, target - rec.p);
  attenuation = albedo->value(0,0, rec.p);
  return true;
}

bool metal::scatter(const ray& r, const hit_record& rec,
		    vec3& attenuation, ray& scattered) {
  vec3 reflected = reflect(r.direction(), rec.normal);
  scattered = ray(rec.p,reflected + fuzz*random_in_unit_ball());
  attenuation = albedo;
  return dot(scattered.direction(),rec.normal) > 0;
}

bool dialectric::scatter(const ray& r_in, const hit_record& rec,
			 vec3& attenuation, ray& scattered) {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ratio;
    attenuation = vec3(1.0,1.0,1.0);
    vec3 refracted;
    float reflect_prob;
    float cosine;
    if (dot(r_in.direction(), rec.normal) > 0) {
      outward_normal = -rec.normal;
      ratio = ri; // air has RI of 1
      cosine = ri*dot(r_in.direction(),rec.normal) / r_in.direction().length();
    }
    else {
      outward_normal = rec.normal;
      ratio = 1.0 / ri; // air has RI of 1
      cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if (refract(r_in.direction(), outward_normal, ratio, refracted)) {
      reflect_prob = schlick(cosine, ri);
    }
    else {
      reflect_prob = 1.0;
    }
    if (rz1() < reflect_prob) {
      scattered = ray(rec.p, reflected);
    }
    else {
      scattered = ray(rec.p, refracted);
    }
    return true;
  }


