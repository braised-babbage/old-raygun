util.o: util.h util.cpp
	c++ -std=c++0x -c util.cpp -o util.o

camera.o: camera.h camera.cpp
	c++ -std=c++0x -c camera.cpp -o camera.o

scene.o: scene.h scene.cpp ray.h vec3.h
	c++ -std=c++0x -c scene.cpp -o scene.o

bvh.o: aabb.h bvh.h bvh.cpp hitable.h util.h
	c++ -std=c++0x -c bvh.cpp -o bvh.o

material.o: material.h material.cpp
	c++ -std=c++0x -c material.cpp -o material.o

raygun.o: aabb.h camera.h sphere.h hitable.h hitable_list.h ray.h vec3.h raygun.cpp
	c++ -std=c++0x -c raygun.cpp -o raygun.o

raygun: camera.o material.o scene.o util.o raygun.o
	c++ -std=c++0x util.o material.o camera.o scene.o raygun.o -o raygun
