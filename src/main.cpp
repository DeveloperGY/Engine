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
		if(fw::Engine::isButtonPressed(fw::MouseButton::Left) && !fw::Engine::getComponent<Sound>(entity).sounds.at("Laser").playing)
		{
			fw::Engine::getComponent<Sound>(entity).sounds.at("Laser").shoudlPlay = true;
		}
		if(fw::Engine::isKeyPressed(fw::Key::Space) && !fw::Engine::getComponent<Sound>(entity).sounds.at("Jump").playing)
		{
			fw::Engine::getComponent<Sound>(entity).sounds.at("Jump").shoudlPlay = true;
		}
		if(fw::Engine::isKeyPressed(fw::Key::Enter) && !fw::Engine::getComponent<Music>(entity).songs.at("Song_1").playing)
		{
			fw::Engine::getComponent<Music>(entity).songs.at("Song_1").shouldPlay = true;
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
	fw::Engine::addSystemRequirement<Music, ShootSystem>();

	// Add a texture 
	fw::Engine::addTexture(100, 100, "test", "test.png");

	// Add a sound
	fw::Engine::addSound("laser", "/home/gydev/Documents/dev/C_C++/Engine/bin/laserShoot.wav");
	fw::Engine::addSound("jump", "/home/gydev/Documents/dev/C_C++/Engine/bin/jump.wav");

	// Add a song
	fw::Engine::addMusic("MySong", "/home/gydev/Documents/dev/C_C++/Engine/bin/song.ogg");

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
		fw::Engine::getComponent<Sprite>(e).frameWidth = 100;
		fw::Engine::getComponent<Sprite>(e).frameHeight = 100;
		fw::Engine::getComponent<Sprite>(e).addAnimation("idle", 0, 4, 0.5);
		fw::Engine::getComponent<Sprite>(e).setAnimation("idle");

		fw::Engine::addComponent<Sound>(e);
		fw::Engine::getComponent<Sound>(e).addSound("Laser", "laser");
		fw::Engine::getComponent<Sound>(e).addSound("Jump", "jump");

		fw::Engine::addComponent<Music>(e);
		fw::Engine::getComponent<Music>(e).addMusic("Song_1", "MySong");
	}, "Main");

	// Load the main scene
	fw::Engine::loadScene("Main");

	// Run the game
	fw::Engine::run();
	return 0;
}