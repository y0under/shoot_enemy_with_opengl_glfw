CFLAGS = -std=c++20 -O2
# LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
LDFLAGS = -lglew -lglfw -framework OpenGL
OUT_DIR = bin

glfw_test: src/main.cc bin/object bin/player bin/game bin/enemy bin/circle bin/player_bullet bin/shader_operator
	g++ $(CFLAGS) -o bin/glfw_test $^ $(LDFLAGS) -D NDEBUG

bin/game: src/game.cc src/game.h bin/object bin/player bin/colliding bin/player_bullet bin/shader_operator
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

debug: src/main.cc
	g++ $(CFLAGS) -o bin/glfw_test src/main.cc $(LDFLAGS) -g

bin/object: src/object.cc src/object.h
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

bin/player: src/player.cc src/player.h bin/object
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

bin/enemy: src/enemy.cc src/enemy.h
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

bin/circle: src/circle.cc src/circle.h
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

bin/colliding: src/colliding.h
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

bin/player_bullet: src/player_bullet.cc src/player_bullet.h
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

bin/shader_operator: src/shader_operator/shader_operator.cc src/shader_operator/shader_operator.h
	g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS) -g

.PHONY: test clean

test: bin/glfw_test
	./bin/glfw_test

run: bin/glfw_test
	./bin/glfw_test

clean:
	rm -f ./bin/*
