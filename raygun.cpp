#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>
#include "ray.h"
#include "vec3.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "util.h"

const float FLOAT_MAX = std::numeric_limits<float>::max();


vec3 color(const ray& r, std::shared_ptr<hitable> world, int depth = 0) {
  
  hit_record rec;
  if (world->hit(r, 0.0, FLOAT_MAX, rec)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered)) {
      return attenuation*color(scattered, world, depth+1);
    }
    else {
      return vec3(0,0,0);
    }
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
  hitable* list[2];
  material *mlist[2];
  mlist[0] = new lambertian(vec3(0.8,0.3,0.3));
  mlist[1] = new lambertian(vec3(0.8,0.8,0.0));
  list[0] = new sphere(vec3(0,0,-1), 0.5, mlist[0]);
  list[1] = new sphere(vec3(0,-100.5,-1), 100, mlist[1]);
  std::shared_ptr<hitable_list> world{new hitable_list()};
  world->add(std::shared_ptr<hitable>(list[0]));
  world->add(std::shared_ptr<hitable>(list[1]));

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

      // gamma 2 correction
      col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      
      int ir = int(255.99*col.r());
      int ig = int(255.99*col.g());
      int ib = int(255.99*col.b());
      
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
      
