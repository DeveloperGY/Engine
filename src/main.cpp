#define MAX_ENTITIES 10000

#include "framework/Engine.hpp"

#include <iostream>
#include <string>

int main(void)
{
	if(!fw::Engine::init("My Game"))
	{
		std::cerr << "ERROR: Failed to initialize engine!" << std::endl;
		return -1;
	}

	fw::Engine::createScene("Main");
	fw::Engine::addTexture(100, 100, "mySprite", "thisismyfilepath/file");

	std::function<void()> mainLoad = []() -> void {
		Entity e = fw::Engine::createEntity();
		fw::Engine::addComponent<fw::Transform>(e);
		fw::Engine::addComponent<fw::Sprite>(e);
		fw::Engine::getComponent<fw::Transform>(e).x = 10;
		fw::Engine::getComponent<fw::Transform>(e).y = 10;
		fw::Sprite s = fw::Engine::getComponent<fw::Sprite>(e);
		s.texture_key = "mySprite";
	};

	fw::Engine::setSceneLoad(mainLoad, "Main");

	fw::Engine::loadScene("Main");

	fw::Engine::run();
	return 0;
}