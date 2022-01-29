#include "Engine.hpp"

fw::Window fw::Engine::win{};
fw::SceneManager fw::Engine::scene_man{};
fw::AssetManager fw::Engine::asset_man{};
bool fw::Engine::running = false;

int fw::Engine::init(std::string p_title, unsigned int p_width, unsigned int p_height)
{
	win.init(p_width, p_height, p_title);
	scene_man.init();

	// register components
	fw::Engine::registerComponent<fw::Transform>();
	fw::Engine::registerComponent<fw::Sprite>();

	//register systems

	fw::Engine::registerSystem<fw::Renderer>();
	fw::Engine::addSystemRequirement<fw::Transform, fw::Renderer>();
	fw::Engine::addSystemRequirement<fw::Sprite, fw::Renderer>();

	running = true;
	return 1;
}

void fw::Engine::run()
{
	sf::Clock clock;
	clock.restart();
	float dt = 0;

	while(running)
	{
		dt = clock.getElapsedTime().asSeconds();
		clock.restart();
		
		win.clear();

		scene_man.update(dt);

		win.display();

		win.pollEvents();
		if(win.shouldClose())
		{
			win.close();
			exit();
		}
	}
	return;
}

void fw::Engine::exit()
{
	running = false;
	return;
}