#ifndef CAMERAH
#define CAMERAH

#include "vec3.hpp"
#include "ray.hpp"
#include "util.hpp"

class camera
{
public:
  camera(vec3 lookfrom, vec3 lookat, vec3 vup,
	 float vfov, float aspect, float aperture, float focus_dist,
	 float time0, float time1);
  
  ray get_ray(float s, float t);
  
private:
  
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 origin;
  vec3 u, v, w;
  float lens_radius;
  float time0, time1;
};

#endif
