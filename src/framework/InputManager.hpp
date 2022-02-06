#pragma once

#include <SFML/Window.hpp>
#include <string>
#include <iostream>

namespace fw
{
	struct Key
	{
		enum Keys
		{
			Unknown = -1, A = 0, B, C,
			D, E, F, G,
			H, I, J, K,
			L, M, N, O,
			P, Q, R, S,
			T, U, V, W,
			X, Y, Z, Num0,
			Num1, Num2, Num3, Num4,
			Num5, Num6, Num7, Num8,
			Num9, Escape, LControl, LShift,
			LAlt, LSystem, RControl, RShift,
			RAlt, RSystem, Menu, LBracket,
			RBracket, Semicolon, Comma, Period,
			Quote, Slash, Backslash, Tilde,
			Equal, Hyphen, Space, Enter,
			Backspace, Tab, PageUp, PageDown,
			End, Home, Insert, Delete,
			Add, Subtract, Multiply, Divide,
			Left, Right, Up, Down,
			Numpad0, Numpad1, Numpad2, Numpad3,
			Numpad4, Numpad5, Numpad6, Numpad7,
			Numpad8, Numpad9, F1, F2,
			F3, F4, F5, F6,
			F7, F8, F9, F10,
			F11, F12, F13, F14,
			F15, Pause, KeyCount, Dash = Hyphen,
			BackSpace = Backspace, BackSlash = Backslash, SemiColon = Semicolon, Return = Enter
		};
	};

	struct MouseButton
	{
		enum MouseButtons
		{
			Left, Right, Middle, XButton1,
			XButton2, ButtonCount
		};
	};

	class InputManager
	{
		private:

		public:

			/**
			 * @brief Initializes the Input Manager
			 * 
			 */
			void init();

			/**
			 * @brief Returns true if the specified key is pressed
			 * 
			 * @return true 
			 * @return false 
			 */
			bool isKeyPressed(fw::Key::Keys);

			/**
			 * @brief Returns true if the specified mouse button is pressed
			 * 
			 * @return true 
			 * @return false 
			 */
			bool isButtonPressed(fw::MouseButton::MouseButtons);

			/**
			 * @brief Retrieves the x position of the mouse relative to the window
			 * 
			 * @return int 
			 */
			int getMouseX(sf::Window& win);

			/**
			 * @brief Retrieves the y position of the mouse relative to the window
			 * 
			 * @return int 
			 */
			int getMouseY(sf::Window& win);
	};
}