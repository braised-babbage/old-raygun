#ifndef CAMERAH
#define CAMERAH

#include "vec3.h"
#include "ray.h"

class camera
{
 public:
  camera(vec3 lookfrom, vec3 lookat, vec3 vup,
	 float vfov, float aspect) {
    // vfov is the angle from top to bottom, in degrees
    float theta = vfov*M_PI/180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;

    origin = lookfrom;
    
    vec3 w = unit_vector(lookfrom - lookat);
    vec3 u = unit_vector(cross(vup, w));
    vec3 v = cross(w, u);

    lower_left_corner = origin - half_width*u - half_height*v - w;
    horizontal = 2*half_width*u;
    vertical = 2*half_height*v;
  }
  ray get_ray(float s, float t) {
    return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
  }

  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 origin;
};

#endif
