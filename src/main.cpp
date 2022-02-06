#define MAX_ENTITIES 10000

#include "framework/Framework.hpp"

#include <iostream>
#include <string>

class ExitSystem: public fw::System
{
	private:

	public:
		void run(Entity e, float dt) override
		{
			if(fw::Engine::isKeyPressed(fw::Key::Escape))
			{
				fw::Engine::stop();
			}
			return;
		}
};

class ShootSystem: public fw::System
{
	private:

	public:
	void run(Entity entity, float dt) override
	{
		if(fw::Engine::isButtonPressed(fw::MouseButton::Left))
		{
			if(!fw::Engine::getComponent<Sound>(entity).playing)
			{
				fw::Engine::getComponent<Sound>(entity).shoudlPlay = true;
			}
		}
		return;
	}
};

struct Exit {};

int main(void)
{
	// Initialize the framework
	if(!fw::init("Arcana doods", 720, 480))
		return -1;

	// Link exit to escape
	fw::Engine::registerSystem<ExitSystem>();
	fw::Engine::registerComponent<Exit>();
	fw::Engine::addSystemRequirement<Exit, ExitSystem>();

	// Allow Shoot Sound
	fw::Engine::registerSystem<ShootSystem>();
	fw::Engine::addSystemRequirement<Sound, ShootSystem>();

	// Add a texture
	fw::Engine::addTexture(100, 100, "test", "test.png");

	// Add a sound
	fw::Engine::addSound("test", "/home/gydev/Documents/dev/C_C++/Engine/bin/laserShoot.wav");

	// Create a scene
	fw::Engine::createScene("Main");

	// Set what happens when the scene should load
	fw::Engine::setSceneLoad([](){
		Entity exit = fw::Engine::createEntity();
		fw::Engine::addComponent<Exit>(exit);

		Entity e = fw::Engine::createEntity();
		fw::Engine::addComponent<Transform>(e);
		fw::Engine::getComponent<Transform>(e).x = 100;
		fw::Engine::getComponent<Transform>(e).y = 100;
		fw::Engine::addComponent<Sprite>(e);
		fw::Engine::getComponent<Sprite>(e).texture = "test";
		fw::Engine::addComponent<Sound>(e);
		fw::Engine::getComponent<Sound>(e).sound = "test";
		fw::Engine::getComponent<Sound>(e).shoudlPlay = true;
	}, "Main");

	// Load the main scene
	fw::Engine::loadScene("Main");

	// Run the game
	fw::Engine::run();
	return 0;
}