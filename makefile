CFLAGS = -std=c++20 -O2
# LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
LDFLAGS = -lglew -lglfw -framework OpenGL
OUT_DIR = bin

glfw_test: src/main.cc bin/object
	g++ $(CFLAGS) -o bin/glfw_test $^ $(LDFLAGS) -D NDEBUG

debug: src/main.cc
	g++ $(CFLAGS) -o bin/glfw_test src/main.cc $(LDFLAGS) -g

bin/object: src/object.cc src/object.h
	g++ $(CFLAGS) -c -o bin/$@ src/object.cc $(LDFLAGS) -g

.PHONY: test clean

test: bin/glfw_test
	./bin/glfw_test

run: bin/glfw_test
	./bin/glfw_test

clean:
	rm -f ./bin/glfw_test
