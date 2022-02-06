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
			float mouseScroll{0};

		public:

			/**
			 * @brief Initializes the window
			 * 
			 * @param int 
			 * @param int 
			 */
			void init(unsigned int, unsigned int, std::string);
			
			/**
			 * @brief Returns true if the window should close
			 * 
			 * @return true 
			 * @return false 
			 */
			bool shouldClose();

			/**
			 * @brief polls user input
			 * 
			 */
			void pollEvents();
			
			/**
			 * @brief Closes the window
			 * 
			 */
			void close();
			
			/**
			 * @brief Draws a sprite to the display
			 * 
			 */
			void draw(sf::Drawable&);
			
			/**
			 * @brief Clears the display
			 * 
			 */
			void clear();
			
			/**
			 * @brief Updates the display
			 * 
			 */
			void display();

			/**
			 * @brief Retrieves the sf::Window
			 * 
			 * @return sf::Window& 
			 */
			sf::Window& getWindow();

			/**
			 * @brief Retrieves the scroll amount since the previous frame
			 * 
			 * @return float 
			 */
			float getScroll();

			/**
			 * @brief Returns true if the window has focus
			 * 
			 * @return true 
			 * @return false 
			 */
			bool hasFocus();
	};
}