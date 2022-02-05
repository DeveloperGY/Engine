#pragma once

#include "Engine.hpp"

namespace fw
{
	/**
	 * @brief Initializes the framework
	 * 
	 * @param title 
	 * @param width 
	 * @param height 
	 * @return int 
	 */
	int init(std::string title, unsigned int width = 720, unsigned int height = 480)
	{
		if(!fw::Engine::init(title, width, height))
		{
			std::cerr << "ERROR: Failed to initialize engine!" << std::endl;
			return 0;
		}

		fw::Engine::registerComponent<fw::Transform>();
		fw::Engine::registerComponent<fw::Sprite>();

		fw::Engine::registerSystem<fw::Renderer>();
		fw::Engine::addSystemRequirement<Transform, fw::Renderer>();
		fw::Engine::addSystemRequirement<Sprite, fw::Renderer>();

		return 1;
	}
}