#include "Engine.hpp"

fw::Window fw::Engine::win{};
bool fw::Engine::running = false;

int fw::Engine::init(std::string p_title, unsigned int p_width, unsigned int p_height)
{
	win.init(p_width, p_height, p_title);



	running = true;
	return 1;
}

void fw::Engine::run()
{
	while(running)
	{
		win.clear();



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