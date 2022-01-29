#pragma once

#include <SFML/Graphics.hpp>

#include <string>

namespace fw
{
	class Window
	{
		private:
			sf::RenderWindow win;
			bool request_close = false;

		public:
			void init(unsigned int, unsigned int, std::string);
			
			bool shouldClose();
			void pollEvents();
			void close();
			void draw(sf::Drawable& d);
			void clear();
			void display();
	};
}