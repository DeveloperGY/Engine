#include "InputManager.hpp"

void fw::InputManager::init()
{
	return;
}

bool fw::InputManager::isKeyPressed(fw::Key::Keys key)
{
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}

bool fw::InputManager::isButtonPressed(fw::MouseButton::MouseButtons button)
{
	return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

int fw::InputManager::getMouseX(sf::Window& win)
{
	return sf::Mouse::getPosition(win).x;
}

int fw::InputManager::getMouseY(sf::Window& win)
{
	return sf::Mouse::getPosition(win).y;
}