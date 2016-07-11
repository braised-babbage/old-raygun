#ifndef RECTH
#define RECTH

#include <memory>
#include "hitable.hpp"

const float BB_TOL = 0.0001;

class xy_rect : public hitable {
public:
  xy_rect() {}
  xy_rect(float x0, float x1, float y0, float y1, float k,
	  std::shared_ptr<material> mat) :
    x0(x0), x1(x1), y0(y0), y1(y1), k(k), mat(mat) {}
  virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const {
    box = aabb(vec3(x0, y0, k - BB_TOL), vec3(x1,y1,k+BB_TOL));
    return true;
  }
private:
  float x0, x1, y0, y1, k;
  std::shared_ptr<material> mat;
};

class xz_rect : public hitable {
public:
  xz_rect() {}
  xz_rect(float x0, float x1, float z0, float z1, float k,
	  std::shared_ptr<material> mat) :
    x0(x0), x1(x1), z0(z0), z1(z1), k(k), mat(mat) {}
  virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const {
    box = aabb(vec3(x0, k-BB_TOL, z0), vec3(x1, k+BB_TOL, z1));
    return true;
  }
private:
  float x0, x1, z0, z1, k;
  std::shared_ptr<material> mat;
};

class yz_rect : public hitable {
public:
  yz_rect() {}
  yz_rect(float y0, float y1, float z0, float z1, float k,
	  std::shared_ptr<material> mat) :
    y0(y0), y1(y1), z0(z0), z1(z1), k(k), mat(mat) {}
  virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const {
    box = aabb(vec3(k-BB_TOL, y0, z0), vec3(k+BB_TOL, y1, z1));
    return true;
  }
private:
  float y0, y1, z0, z1, k;
  std::shared_ptr<material> mat;
};

#endif
