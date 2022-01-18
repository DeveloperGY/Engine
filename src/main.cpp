#define MAX_ENTITIES 10000

#include "framework/Engine.hpp"

#include <iostream>
#include <string>

struct MyComponent
{
	int x{};
};

int main(void)
{
	if(!fw::Engine::init("My Game"))
	{
		std::cerr << "ERROR: Failed to initialize engine!" << std::endl;
		return -1;
	}

	fw::SystemManager sm;

	fw::Engine::run();
	return 0;
}