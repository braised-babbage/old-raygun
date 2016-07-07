#ifndef PERLINH
#define PERLINH

#include <cmath>
#include "util.h"
#include "vec3.h"
#include "texture.h"



class perlin {
public:
  float noise(const vec3& p) const;
private:
  static vec3 *ranvec;
  static int *perm_x;
  static int *perm_y;
  static int *perm_z;
};

class noise_texture : public texture {
public:
  noise_texture(float sc = 1.0f) : scale(sc) { }
  virtual vec3 value(float u, float v, const vec3& p) const{
    return vec3(1,1,1)*0.5*(1 + noise.noise(scale*p));
  }
private:
  perlin noise;
  float scale;
};

#endif
