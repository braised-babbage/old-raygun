CC=c++
CFLAGS=-c -std=c++0x -Wall
LDFLAGS=
SOURCES=util.cpp camera.cpp scene.cpp bvh.cpp material.cpp raygun.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=raygun

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
