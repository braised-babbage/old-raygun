#ifndef SCENEH
#define SCENEH

#include <iostream>
#include <memory>
#include "hitable.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "camera.hpp"

// A scene consists of a world and a camera.
// It may be rendered to an output stream.

class scene
{
public:
  scene(std::shared_ptr<hitable> world, std::shared_ptr<camera> cam)
    : world(world), cam(cam)
  {}

  void render(int nx, int ny, int rpp, std::ostream& os);
  
protected:
  vec3 color(const ray& r, int depth = 0);

private:
  std::shared_ptr<hitable> world;
  std::shared_ptr<camera> cam;
};


#endif
