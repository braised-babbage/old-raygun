#ifndef SCENEH
#define SCENEH

#include <iostream>
#include <memory>
#include "hitable.h"
#include "ray.h"
#include "vec3.h"
#include "camera.h"

class scene
{
public:
  scene(std::shared_ptr<hitable> world, std::shared_ptr<camera> cam)
    : world(world), cam(cam)
  {}
  vec3 color(const ray& r, int depth = 0);

  void render(int nx, int ny, int rpp, std::ostream& os);

 private:
  std::shared_ptr<hitable> world;
  std::shared_ptr<camera> cam;
};


#endif
