#define MAX_ENTITIES 10000

#include "framework/Engine.hpp"

#include <iostream>
#include <string>

struct Transform
{
	float x = 0;
	float y = 0;
};

int main(void)
{
	if(!fw::Engine::init("My Game"))
	{
		std::cerr << "ERROR: Failed to initialize engine!" << std::endl;
		return -1;
	}

	fw::Engine::registerComponent<Transform>();

	fw::Engine::createScene("Main");

	fw::Engine::setSceneLoad([](){
		Entity e = fw::Engine::createEntity();
		fw::Engine::addComponent<Transform>(e);
		fw::Engine::getComponent<Transform>(e).x = 5;
	}, "Main");

	fw::Engine::loadScene("Main");

	fw::Engine::run();
	return 0;
}