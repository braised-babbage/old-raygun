#ifndef TEXTUREH
#define TEXTUREH

#include <memory>
#include <cmath>
#include "vec3.h"

class texture {
public:
  virtual vec3 value(float u, float v, const vec3& p) const  = 0;
};

class constant_texture : public texture {
public:
  constant_texture(vec3 c) : color(c) {}
  virtual vec3 value(float u, float v, const vec3& p) const {
    return color;
  }

private:
  vec3 color;
};

class checker_texture : public texture {
public:
  checker_texture(std::shared_ptr<texture> t0,
		  std::shared_ptr<texture> t1)
  { even = t0; odd = t1; }
  virtual vec3 value(float u, float v, const vec3& p) const {
    float sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
    return sines < 0 ? odd->value(u,v,p) : even->value(u,v,p);
  }
private:
  std::shared_ptr<texture> even, odd;
};

#endif
