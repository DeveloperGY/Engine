src = src/**/**/*.cpp src/**/*.cpp src/*.cpp
flags = -std=c++17 -Wall -Wextra
libs = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

make: build

build:
	g++ $(src) -o bin/exe $(flags) $(libs)

debug:
	g++ $(src) -o bin/debug $(flags) -g -fsanitize=address $(libs)

run:
	./bin/exe