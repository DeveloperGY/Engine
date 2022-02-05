#include "Window.hpp"

void fw::Window::init(unsigned int p_width, unsigned int p_height, std::string p_title)
{
	this->win.create(sf::VideoMode(p_width, p_height), p_title, sf::Style::Close | sf::Style::Titlebar);
	return;
}

void fw::Window::draw(sf::Drawable& sprite)
{
	this->win.draw(sprite);
	return;
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
		this->mouseScroll = 0;
		if(e.type == sf::Event::Closed)
		{
			this->request_close = true;
		}
		else if(e.type == sf::Event::MouseWheelScrolled)
		{
			if(e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{
				this->mouseScroll = e.mouseWheelScroll.delta;
			}
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
	this->win.clear(sf::Color(22, 22, 29));
	return;
}

void fw::Window::display()
{
	this->win.display();
	return;
}

sf::Window& fw::Window::getWindow()
{
	return this->win;
}

float fw::Window::getScroll()
{
	return this->mouseScroll;
}