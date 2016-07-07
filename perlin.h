#ifndef PERLINH
#define PERLINH

#include <cmath>
#include "util.h"
#include "vec3.h"
#include "texture.h"

class perlin {
public:
  float noise(const vec3& p) const {
    float u = p.x() - floor(p.x());
    float v = p.y() - floor(p.y());
    float w = p.z() - floor(p.z());
    int i = int(4*p.x()) & 255;
    int j = int(4*p.y()) & 255;
    int k = int(4*p.z()) & 255;
    return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
  }
private:
  static float *ranfloat;
  static int *perm_x;
  static int *perm_y;
  static int *perm_z;
};

class noise_texture : public texture {
public:
  noise_texture() {}
  virtual vec3 value(float u, float v, const vec3& p) const{
    return vec3(1,1,1)*noise.noise(p);
  }
private:
  perlin noise;
};

#endif
