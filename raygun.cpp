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
  if (world->hit(r, 0.001, FLOAT_MAX, rec)) {
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

std::shared_ptr<hitable> random_world(int n = 3) {
  std::shared_ptr<hitable> item;
  std::shared_ptr<hitable_list> world{new hitable_list()};

  // ground
  item = std::shared_ptr<hitable>(new sphere(vec3(0,-1000,0), 1000,
					     new lambertian(vec3(0.5, 0.5, 0.5))));
  world->add(item);
  
  for (int a = -n; a < n; a++) {
    for (int b = -n; b < n; b++) {
      material* mat;
      float choose_mat = rz1();
      vec3 center(a+0.9*rz1(), 0.2, b + 0.9*rz1());
      // minimal distance
      //      if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
	if (choose_mat < 0.8) { // diffuse
	  mat = new lambertian(vec3(rz1()*rz1(),
				    rz1()*rz1(),
				    rz1()*rz1()));
	}
	else if (choose_mat < 0.95) { // metal
	  mat = new metal(vec3(0.5*(1 + rz1()),
			       0.5*(1 + rz1()),
			       0.5*(1 + rz1())),
			  0.5*rz1());
	}
	else { // glass
	  mat = new dialectric(1.5);
	}
	item = std::shared_ptr<hitable>(new sphere(center, 0.2, mat));
	world->add(item);
	//      }
    }
  }


  item = std::shared_ptr<hitable>(new sphere(vec3(0, 1, 0),
					     1.0,
					     new dialectric(1.5)));
  world->add(item);

  item = std::shared_ptr<hitable>(new sphere(vec3(-4, 1, 0),
					     1.0,
					     new lambertian(vec3(0.4, 0.2, 0.1))));
  world->add(item);

  item = std::shared_ptr<hitable>(new sphere(vec3(4,1,0),
					     1.0,
					     new metal(vec3(0.7, 0.6, 0.5), 0.0)));
  world->add(item);

  return world;
}

std::shared_ptr<hitable> camera_test_world()
{
  std::shared_ptr<hitable> item;
  std::shared_ptr<hitable_list> world(new hitable_list());

  float R = cos(M_PI/4.0);
  item = std::shared_ptr<hitable>(new sphere(vec3(-R, 0, -1), R,
					     new lambertian(vec3(0, 0, 1))));
  world->add(item);

  item = std::shared_ptr<hitable>(new sphere(vec3(R, 0, -1), R,
					     new lambertian(vec3(1,0,0))));
  world->add(item);

  return world;
}

std::shared_ptr<hitable> make_world()
{
  std::shared_ptr<hitable> item;
  std::shared_ptr<hitable_list> world{new hitable_list()};
  

  item = std::shared_ptr<hitable>(new sphere(vec3(0,0,-1), 0.5,
					     new lambertian(vec3(0.1,0.2,0.5))));
  world->add(item);

  item = std::shared_ptr<hitable>(new sphere(vec3(0,-100.5,-1), 100,
					     new lambertian(vec3(0.8,0.8,0.0))));
  world->add(item);

  item = std::shared_ptr<hitable>(new sphere(vec3(1,0,-1), 0.5,
					     new metal(vec3(0.8,0.6,0.2),0.3)));
  world->add(item);

  //bubble
  item = std::shared_ptr<hitable>(new sphere(vec3(-1,0,-1), 0.5,
					     new dialectric(1.5)));
  world->add(item);
  item = std::shared_ptr<hitable>(new sphere(vec3(-1,0,-1), -0.45,
					     new dialectric(1.5)));
  world->add(item);
  
  return world;
}

int main() {
  int nx = 800;
  int ny = 400;
  int rays_per_pixel = 100;
  
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  float s = 1.4;
  vec3 lookfrom(12/s,2.5/s,3.5/s);
  vec3 lookat(2,0.5,0.2);
  float dist_to_focus = (lookfrom-lookat).length();
  float aperture = 0.05;
  
  camera cam(lookfrom, lookat, vec3(0,1,0),30, float(nx)/float(ny),
	     aperture, dist_to_focus);
  std::shared_ptr<hitable> world = random_world(11);
  
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
      
