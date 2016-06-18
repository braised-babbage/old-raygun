# Raygun

Raygun is a simple raytracer, written in C++. It can make strange pictures,
such as ![random spheres](http://i.imgur.com/4fHHTtO.png "Random Spheres")

## Features

Right now, things are pretty minimal. Scenes (i.e. a bunch of *spheres*, with various material properties) are hardcoded, and the output is in text ppm format. 

### Materials
Currently Raygun supports the following materials:
* `lambertian` for matte objects
* `metal` for reflecting objects
* `dielectric` for refracting/reflecting objects (e.g. glass)
