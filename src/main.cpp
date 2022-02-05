#define MAX_ENTITIES 10000

#include "framework/Framework.hpp"

#include <iostream>
#include <string>

int main(void)
{
	// Initialize the framework
	if(!fw::init("Arcana doods", 720, 480))
		return -1;

	// Add a texture
	fw::Engine::addTexture(100, 100, "test", "bin/test.png");

	// Create a scene
	fw::Engine::createScene("Main");

	// Set what happens when the scene should load
	fw::Engine::setSceneLoad([](){
		Entity e = fw::Engine::createEntity();
		fw::Engine::addComponent<Transform>(e);
		fw::Engine::getComponent<Transform>(e).x = 100;
		fw::Engine::getComponent<Transform>(e).y = 100;
		fw::Engine::addComponent<Sprite>(e);
		fw::Engine::getComponent<Sprite>(e).texture = "test";
	}, "Main");

	// Load the main scene
	fw::Engine::loadScene("Main");

	// Run the game
	fw::Engine::run();
	return 0;
}