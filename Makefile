CC=c++
CFLAGS=-c -std=c++0x -Wall -O3
LDFLAGS=
SOURCES=util.cpp aabb.cpp camera.cpp scene.cpp bvh.cpp \
	sphere.cpp material.cpp perlin.cpp rect.cpp \
	raygun.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=raygun

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
