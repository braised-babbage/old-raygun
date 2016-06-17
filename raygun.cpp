#include <iostream>
#include <limits>
#include <cstdlib>
#include "ray.h"
#include "vec3.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"

const float FLOAT_MAX = std::numeric_limits<float>::max();

vec3 linear_interpolate(const vec3 &v1, const vec3 &v2, float t) {
  return v1*(1.0-t) + v2*t;
}

// TODO : c++ style rng?
double rz1() // random zero to one
{
    return rand() / (RAND_MAX + 1.);
}

vec3 random_in_unit_ball() {
  vec3 p;
  do {
    p = 2.0*vec3(rz1(), rz1(), rz1()) - vec3(1,1,1);
  } while (dot(p,p) >= 1.0);
  return p;
}

vec3 color(const ray& r, hitable *world) {
  vec3 center(0,0,-1);
  sphere s(center, 0.5);
  
  hit_record rec;
  if (world->hit(r, 0.0, FLOAT_MAX, rec)) {
    vec3 target = rec.p + rec.normal + random_in_unit_ball();
    return 0.5*color(ray(rec.p, target - rec.p), world);
 // return 0.5*vec3(rec.normal.x() + 1,
 // 		    rec.normal.y() + 1,
 // 		    rec.normal.z() + 1);
  }
  else {
  // background gradient
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return linear_interpolate(vec3(1.0,1.0,1.0), vec3(0.5,0.7,1.0), t);
  }
}

int main() {
  int nx = 200;
  int ny = 100;
  int rays_per_pixel = 100;
  
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";
  hitable *list[2];
  list[0] = new sphere(vec3(0,0,-1), 0.5);
  list[1] = new sphere(vec3(0,-100.5,-1), 100);
  hitable *world = new hitable_list(list,2);
  camera cam;
  
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0,0,0);
      for (int s = 0; s < rays_per_pixel; s++) {
	// lower left corner + random offsets
	float u = (float(i) + rz1()) / float(nx);
	float v = (float(j) + rz1()) / float(ny);
	ray r = cam.get_ray(u, v);
	col += color(r, world);
      }
      col /= float(rays_per_pixel);
      
      int ir = int(255.99*col.r());
      int ig = int(255.99*col.g());
      int ib = int(255.99*col.b());
      
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
      
