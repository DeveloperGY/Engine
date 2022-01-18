#include "Window.hpp"

void fw::Window::init(unsigned int p_width, unsigned int p_height, std::string p_title)
{
	this->win.create(sf::VideoMode(p_width, p_height), p_title, sf::Style::Close | sf::Style::Titlebar);
	return;
}

void fw::Window::draw()
{
	//TODO: make draw method
}

bool fw::Window::shouldClose()
{
	return this->request_close;
}

void fw::Window::pollEvents()
{
	sf::Event e;
	while(this->win.pollEvent(e))
	{
		if(e.type == sf::Event::Closed)
		{
			this->request_close = true;
		}
	}
	return;
}

void fw::Window::close()
{
	this->win.close();
	return;
}

void fw::Window::clear()
{
	this->win.clear();
	return;
}

void fw::Window::display()
{
	this->win.display();
	return;
}