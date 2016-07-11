#include <memory>
#include <vector>
#include "vec3.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "hitable.hpp"
#include "rect.hpp"
#include "bvh.hpp"
#include "transform.hpp"

using std::shared_ptr;
using std::make_shared;

// scene is : camera, world
// depends on nx, ny


shared_ptr<hitable> cornell_box_world() {
  auto red = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.65, 0.05, 0.05)));
  auto white = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.73, 0.73, 0.73)));
  auto green = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.12, 0.45, 0.15)));
  auto light = make_shared<diffuse_light>(make_shared<constant_texture>(vec3(15,15,15)));
  
  std::vector<shared_ptr<hitable> > objects;
  objects.push_back(make_shared<flipped_normals>(make_shared<yz_rect>(0, 555, 0, 555, 555, green)));
  objects.push_back(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
  objects.push_back(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
  objects.push_back(make_shared<flipped_normals>(make_shared<xz_rect>(0, 555, 0, 555, 555, white)));
  objects.push_back(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
  objects.push_back(make_shared<flipped_normals>(make_shared<xy_rect>(0, 555, 0, 555, 555, white)));

  auto b = make_shared<box>(vec3(0,0,0), vec3(165,165,165), white);
  objects.push_back(make_shared<translated>(make_shared<rotated_y>(b, -18), vec3(130,0,65)));
  b =make_shared<box>(vec3(0,0,0), vec3(165,330,165), white);
  objects.push_back(make_shared<translated>(make_shared<rotated_y>(b, 15), vec3(265,0,295)));

  return make_shared<bvh_node>(objects, 0.0, 1.0);
}


shared_ptr<scene> cornell_box(int nx, int ny)
{
  vec3 lookfrom(278, 278, -800);
  vec3 lookat(278, 278, 0);
  float dist_to_focus = 10.0;
  float aperture = 0.0;
  float vfov = 40.0;
  auto cam = make_shared<camera>(lookfrom, lookat, vec3(0,1,0), vfov, float(nx)/float(ny), aperture, dist_to_focus, 0.0, 1.0);
  auto world = cornell_box_world();
  return make_shared<scene>(world, cam);
}




shared_ptr<hitable> simple_lit_world() {
  auto pertext = make_shared<noise_texture>(4.0);
  shared_ptr<material> mat = make_shared<lambertian>(pertext);
  std::vector<shared_ptr<hitable> > objects;

  objects.push_back(make_shared<sphere>(vec3(0,-1000,0), 1000, mat));
  objects.push_back(make_shared<sphere>(vec3(0,2,0), 2, mat));
  
  auto light_texture = make_shared<constant_texture>(vec3(4,4,4));
  mat = make_shared<diffuse_light>(light_texture);
  objects.push_back(make_shared<sphere>(vec3(0,7,0), 2, mat));
  objects.push_back(make_shared<xy_rect>(3, 5, 1, 3, -2,
					 mat));
  return make_shared<bvh_node>(objects, 0.0, 0.1);
}

shared_ptr<scene> simple_lit(int nx, int ny) {
  vec3 lookfrom(13,2,3);
  vec3 lookat(0,0,0);
  float dist_to_focus(10.0);
  float aperture = 0.0;
  
  auto cam = make_shared<camera>(lookfrom, lookat, vec3(0,1,0), 20,
   				 float(nx)/float(ny), aperture, dist_to_focus,
   				 0.0, 1.0);
  auto world = simple_lit_world();

  return make_shared<scene>(world, cam);
}
