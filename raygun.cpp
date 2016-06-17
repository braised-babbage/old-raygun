#include <iostream>
#include "ray.h"
#include "vec3.h"
#include "hitable.h"
#include "sphere.h"

vec3 linear_interpolate(const vec3 &v1, const vec3 &v2, float t) {
  return v1*(1.0-t) + v2*t;
}
/*
float hit_sphere(const vec3& center, float radius, const ray& r) {
  // ray = a + tb
  // want to solve (a + tb - center)^2 = r^2
  // or   b^2 t^2 + t b(a-center) + (a-center)^2 = r^2
  // generally, quadratic ax^2 + bx + c = 0 has solution
  //   (-b +- sqrt(b^2 - 4ac)) / 2a
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - 4*a*c;  
  if (discriminant < 0) {
    return -1.0;
  }
  else {
    return (-b - sqrt(discriminant) ) / (2.0*a);
  }
  }*/

vec3 color(const ray& r) {
  vec3 center(0,0,-1);
  sphere s(center, 0.5);
  
  hit_record rec;
  if (s.hit(r, 0.0, 100.0, rec)) {
    return 0.5*vec3(rec.normal.x() + 1,
		    rec.normal.y() + 1,
		    rec.normal.z() + 1);
  }
  // background gradient
  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5*(unit_direction.y() + 1.0);
  return linear_interpolate(vec3(1.0,1.0,1.0), vec3(0.5,0.7,1.0), t);
}

int main() {
  int nx = 200;
  int ny = 100;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";
  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      ray r = ray(origin, lower_left_corner + u*horizontal + v*vertical);
      vec3 col = color(r);
      int ir = int(255.99*col.r());
      int ig = int(255.99*col.g());
      int ib = int(255.99*col.b());
      
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
      
