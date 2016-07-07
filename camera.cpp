#include "camera.h"
#include "vec3.h"
#include "ray.h"
#include "util.h"

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup,
	       float vfov, float aspect, float aperture, float focus_dist,
	       float t0, float t1)
{
  time0 = t0;
  time1 = t1;
  lens_radius = aperture / 2.0;
  // vfov is the angle from top to bottom, in degrees
  float theta = vfov*M_PI/180;
  float half_height = tan(theta/2);
  float half_width = aspect * half_height;
  
  origin = lookfrom;    
  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);
  
  lower_left_corner =
    origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
  horizontal = 2*half_width*focus_dist*u;
  vertical = 2*half_height*focus_dist*v;
  
}

ray camera::get_ray(float s, float t)
{
  vec3 rd = lens_radius*random_in_unit_disk();
  vec3 offset = u*rd.x() + v*rd.y();
  vec3 c = origin + offset;
  float time = time0 + rz1()*(time1 - time0);
  return ray(c, lower_left_corner + s*horizontal + t*vertical - c, time);
}
