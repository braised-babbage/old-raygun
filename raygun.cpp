#include <iostream>
#include "ray.h"
#include "vec3.h"

vec3 linear_interpolate(const vec3 &v1, const vec3 &v2, float t) {
  return v1*(1.0-t) + v2*t;
}

vec3 color(const ray& r) {
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
      ray r(origin, lower_left_corner + u*horizontal + v*vertical);
      vec3 col = color(r);
      int ir = int(255.99*col.r());
      int ig = int(255.99*col.g());
      int ib = int(255.99*col.b());
      
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
      
