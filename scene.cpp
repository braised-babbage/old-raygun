#include "ray.h"
#include "vec3.h"
#include "scene.h"
#include "util.h"
#include "camera.h"
#include "material.h"

vec3 scene::color(const ray& r, int depth)
{  
  hit_record rec;
  if (world->hit(r, 0.001, FLOAT_MAX, rec)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered)) {
      return attenuation*color(scattered, depth+1);
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

void scene::render(int nx, int ny, int rpp, std::ostream& os)
{
  os << "P3\n" << nx << " " << ny << "\n255\n";
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0,0,0);
      for (int s = 0; s < rpp; s++) {
	// lower left corner + random offsets
	float u = (float(i) + rz1()) / float(nx);
	float v = (float(j) + rz1()) / float(ny);
	ray r = cam->get_ray(u, v);
	col += color(r);
      }
      col /= float(rpp);
      
      // gamma 2 correction
      col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      
      int ir = int(255.99*col.r());
      int ig = int(255.99*col.g());
      int ib = int(255.99*col.b());
      
      os << ir << " " << ig << " " << ib << "\n";
    }
  }
}
