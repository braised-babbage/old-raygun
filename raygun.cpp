#include <iostream>
#include <cstdlib>
#include <memory>
#include "scene.h"
#include "ray.h"
#include "vec3.h"
#include "hitable.h"
#include "hitable_list.h"
#include "bvh.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "util.h"



std::shared_ptr<hitable> random_world(int n = 3) {
  std::shared_ptr<hitable> item;
  std::vector<std::shared_ptr<hitable> > spheres;
  

  // ground
  item = std::shared_ptr<hitable>(new sphere(vec3(0,-1000,0), 1000,
					     new lambertian(vec3(0.5, 0.5, 0.5))));
  spheres.push_back(item);
  
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
	  item = std::shared_ptr<hitable>(new moving_sphere(center, center+vec3(0, 0.5*rz1(), 0),
							    0.0, 1.0, 0.2, mat));
	}
	else if (choose_mat < 0.95) { // metal
	  mat = new metal(vec3(0.5*(1 + rz1()),
			       0.5*(1 + rz1()),
			       0.5*(1 + rz1())),
			  0.5*rz1());
	  item = std::shared_ptr<hitable>(new sphere(center, 0.2, mat));
	}
	else { // glass
	  mat = new dialectric(1.5);
	  item = std::shared_ptr<hitable>(new sphere(center, 0.2, mat));
	}
	spheres.push_back(item);
	//      }
    }
  }


  item = std::shared_ptr<hitable>(new sphere(vec3(0, 1, 0),
					     1.0,
					     new dialectric(1.5)));
  spheres.push_back(item);

  item = std::shared_ptr<hitable>(new sphere(vec3(-4, 1, 0),
					     1.0,
					     new lambertian(vec3(0.4, 0.2, 0.1))));
  spheres.push_back(item);

  item = std::shared_ptr<hitable>(new sphere(vec3(4,1,0),
					     1.0,
					     new metal(vec3(0.7, 0.6, 0.5), 0.0)));
  spheres.push_back(item);

  std::shared_ptr<bvh_node> world(new bvh_node(spheres.begin(), spheres.end(), 0.0, 0.0));
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
  int nx = 200;
  int ny = 100;
  int rays_per_pixel = 20;

  float s = 1.4;
  vec3 lookfrom(12/s,2.5/s,3.5/s);
  vec3 lookat(2,0.5,0.2);
  float dist_to_focus = (lookfrom-lookat).length();
  float aperture = 0.05;
  
  std::shared_ptr<camera> cam{new camera(lookfrom, lookat, vec3(0,1,0),30,
					 float(nx)/float(ny), aperture, dist_to_focus,
					 0.0, 1.0)};
  std::shared_ptr<hitable> world = random_world(11);
  scene rand_scene(world, cam);

  rand_scene.render(nx,ny,rays_per_pixel,std::cout);
}
      
