util.o: util.h util.cpp
	c++ -std=c++0x -c util.cpp -o util.o

aabb.o: aabb.h aabb.cpp ray.h
	c++ -std=c++0x -c aabb.cpp -o aabb.o

camera.o: camera.h camera.cpp
	c++ -std=c++0x -c camera.cpp -o camera.o

scene.o: scene.h scene.cpp ray.h vec3.h
	c++ -std=c++0x -c scene.cpp -o scene.o

material.o: material.h material.cpp
	c++ -std=c++0x -c material.cpp -o material.o

raygun.o: camera.h sphere.h hitable.h hitable_list.h ray.h vec3.h raygun.cpp
	c++ -std=c++0x -c raygun.cpp -o raygun.o

raygun: aabb.o camera.o material.o scene.o util.o raygun.o
	c++ -std=c++0x aabb.o util.o material.o camera.o scene.o raygun.o -o raygun
