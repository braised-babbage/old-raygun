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
#include "texture.h"
#include "perlin.h"
#include "rect.h"
#include "box.h"
#include "test_scenes.h"

using std::shared_ptr;
using std::make_shared;


shared_ptr<hitable> two_perlin_spheres() {
  auto pertext = make_shared<noise_texture>(3.0);
  auto mat = make_shared<lambertian>(pertext);
  std::vector<shared_ptr<hitable> > spheres;

  spheres.push_back(make_shared<sphere>(vec3(0, -1000, 0),
					1000,
					mat));
  spheres.push_back(make_shared<sphere>(vec3(0, 2, 0),
					2,
					mat));
  return make_shared<bvh_node>(spheres.begin(), spheres.end(), 0.0, 1.0);
}



shared_ptr<hitable> random_world(int n = 3) {
  shared_ptr<hitable> item;
  std::vector<shared_ptr<hitable> > spheres;
  shared_ptr<texture> tex;
  shared_ptr<material> mat;

  const float t0 = 0.0f;
  const float t1 = 1.0f;
  
  // ground

  vec3 c0(0.2,0.3,0.1);
  vec3 c1(0.9,0.9,0.9);
  
  tex = make_shared<checker_texture>(make_shared<constant_texture>(c0),
				     make_shared<constant_texture>(c1));
  mat = make_shared<lambertian>(tex);
  item = make_shared<sphere>(vec3(0,-1000,0), 1000, mat);
  spheres.push_back(item);
  
  for (int a = -n; a < n; a++) {
    for (int b = -n; b < n; b++) {
      float choose_mat = rz1();
      vec3 center(a+0.9*rz1(), 0.2, b + 0.9*rz1());
      // minimal distance
      //      if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
	if (choose_mat < 0.8) { // diffuse
	  tex = make_shared<constant_texture>(vec3(rz1()*rz1(),
						   rz1()*rz1(),
						   rz1()*rz1()));
	  mat = make_shared<lambertian>(tex);
	  item = make_shared<moving_sphere>(center,
					    center+vec3(0, 0.5*rz1(),0),
					    t0, t1, 0.2, mat);
	}
	else if (choose_mat < 0.95) { // metal
	  mat = make_shared<metal>(vec3(0.5*(1 + rz1()),
					0.5*(1 + rz1()),
					0.5*(1 + rz1())),
				   0.5*rz1());
	  item = make_shared<sphere>(center, 0.2, mat);
	}
	else { // glass
	  mat = make_shared<dialectric>(1.5);
	  item = make_shared<sphere>(center, 0.2, mat);
	}
	spheres.push_back(item);
	//      }
    }
  }


  mat = make_shared<dialectric>(1.5);
  item = make_shared<sphere>(vec3(0, 1, 0),
			     1.0,
			     mat);
  spheres.push_back(item);

  tex = make_shared<constant_texture>(vec3(0.4,0.2, 0.1));
  mat = make_shared<lambertian>(tex);
  item = make_shared<sphere>(vec3(-4, 1, 0),
			     1.0,
			     mat);
  spheres.push_back(item);

  mat = make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0);
  item = make_shared<sphere>(vec3(4,1,0),
			     1.0,
			     mat);
  spheres.push_back(item);

  auto world = make_shared<bvh_node>(spheres.begin(), spheres.end(), t0, t1);
  return world;
}

// std::shared_ptr<hitable> camera_test_world()
// {
//   std::shared_ptr<hitable> item;
//   std::shared_ptr<hitable_list> world(new hitable_list());

//   float R = cos(M_PI/4.0);
//   item = std::shared_ptr<hitable>(new sphere(vec3(-R, 0, -1), R,
// 					     new lambertian(vec3(0, 0, 1))));
//   world->add(item);

//   item = std::shared_ptr<hitable>(new sphere(vec3(R, 0, -1), R,
// 					     new lambertian(vec3(1,0,0))));
//   world->add(item);

//   return world;
// }

// std::shared_ptr<hitable> make_world()
// {
//   std::shared_ptr<hitable> item;
//   std::shared_ptr<hitable_list> world{new hitable_list()};
  

//   item = std::shared_ptr<hitable>(new sphere(vec3(0,0,-1), 0.5,
// 					     new lambertian(vec3(0.1,0.2,0.5))));
//   world->add(item);

//   item = std::shared_ptr<hitable>(new sphere(vec3(0,-100.5,-1), 100,
// 					     new lambertian(vec3(0.8,0.8,0.0))));
//   world->add(item);

//   item = std::shared_ptr<hitable>(new sphere(vec3(1,0,-1), 0.5,
// 					     new metal(vec3(0.8,0.6,0.2),0.3)));
//   world->add(item);

//   //bubble
//   item = std::shared_ptr<hitable>(new sphere(vec3(-1,0,-1), 0.5,
// 					     new dialectric(1.5)));
//   world->add(item);
//   item = std::shared_ptr<hitable>(new sphere(vec3(-1,0,-1), -0.45,
// 					     new dialectric(1.5)));
//   world->add(item);
  
//   return world;
// }



int main() {
  int nx = 200;
  //int ny = 200;
  int ny = 200;
  int rays_per_pixel = 500;

  //  float s = 1.4;
  //vec3 lookfrom(12/s,2.5/s,3.5/s);
  //vec3 lookat(2,0.5,0.2);
  //float dist_to_focus = (lookfrom-lookat).length();
  //float aperture = 0.05;
  
  //auto cam = make_shared<camera>(lookfrom, lookat, vec3(0,1,0),30,
  //			 float(nx)/float(ny), aperture, dist_to_focus,
  //				 0.0, 1.0);
  //shared_ptr<hitable> world = random_world(11);
  //scene rand_scene(world, cam);
  /////////

  auto box_scene = simple_lit(nx,ny);
  box_scene->render(nx,ny,rays_per_pixel,std::cout);
}
      
