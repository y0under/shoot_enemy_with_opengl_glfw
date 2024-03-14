CFLAGS = -std=c++20 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

glfw_test: src/main.cc
	g++ $(CFLAGS) -o bin/glfw_test src/main.cc $(LDFLAGS) -D NDEBUG

debug: src/main.cc
	g++ $(CFLAGS) -o bin/glfw_test src/main.cc $(LDFLAGS) -g

.PHONY: test clean

test: bin/glfw_test
	./bin/glfw_test

run: bin/glfw_test
	./bin/glfw_test

clean:
	rm -f ./bin/glfw_test
