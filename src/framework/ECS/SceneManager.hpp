#pragma once

#include "ECS_GLOBAL.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

namespace fw
{
	class Scene
	{
		private:
			bool load_set = false;
			std::function<void()> load;

			friend class SceneManager;

		public:
			std::string name;

			void setLoad(std::function<void()> p_onLoad)
			{
				this->load = p_onLoad;
				this->load_set = true;
				return;
			}
	};

	class SceneManager
	{
		private:
			fw::EntityManager entity_man;
			fw::ComponentManager component_man;
			fw::SystemManager system_man;

			std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;

		public:
			void init();

			Scene& createScene(std::string name);
			void loadScene(std::string name);
			void loadScene(fw::Scene& scene);

	};
}