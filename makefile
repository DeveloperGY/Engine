src = src/**/**/*.cpp src/**/*.cpp src/*.cpp
flags = -std=c++17 -Wall -Wextra -O2
libs = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

make: build

build:
	g++ $(src) -o bin/exe $(flags) $(libs)

run:
	./bin/exe