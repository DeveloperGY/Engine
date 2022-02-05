#define MAX_ENTITIES 10000

#include "framework/Framework.hpp"

#include <iostream>
#include <string>

int main(void)
{
	if(!fw::init("My Game", 1440, 960))
		return -1;

	fw::Engine::addTexture(100, 100, "test", "bin/test.png");

	fw::Engine::createScene("Main");

	fw::Engine::setSceneLoad([](){
		Entity e = fw::Engine::createEntity();
		fw::Engine::addComponent<Transform>(e);
		fw::Engine::getComponent<Transform>(e).x = 100;
		fw::Engine::getComponent<Transform>(e).y = 100;
		fw::Engine::addComponent<Sprite>(e);
		fw::Engine::getComponent<Sprite>(e).texture = "test";
	}, "Main");

	fw::Engine::loadScene("Main");

	fw::Engine::run();
	return 0;
}