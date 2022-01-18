#pragma once

#include "Window.hpp"
#include "ECS/ECS.hpp"

namespace fw
{
	class Engine
	{
		private:
			static fw::Window win;

			static bool running;

		public:
			static int init(std::string p_title = "", unsigned int p_width = 720, unsigned int p_height = 480);
			static void run();

			static void exit();
	};
}

// create systems and stuff