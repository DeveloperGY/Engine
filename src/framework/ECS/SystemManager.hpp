#pragma once

#include "ECS_GLOBAL.hpp"

#include <set>
#include <unordered_map>
#include <string>
#include <typeinfo>

namespace fw
{
	class System
	{
		private:
			std::set<Entity> entities;
		
			void update()
			{
				for(Entity e: this->entities)
				{
					this->run(e);
				}
			}

			friend class SystemManager;

		public:
			virtual void run(Entity e) = 0;
	};

	class SystemManager
	{
		private:
		std::unordered_map<std::string, std::shared_ptr<System>> systems;

		public:
			void init();

			template <typename T>
			void registerSystem()
			{
				std::string type = typeid(T).name();
				if(this->systems.find(type) != this->systems.end())
				{
					std::cerr << "WARNING: Failed to register system, system already registered!" << std::endl;
					return;
				}
				else
				{
					this->systems.insert({type, std::make_shared<T>});
					return;
				}
				return;
			}

			void update()
			{
				for(auto& pair: this->systems)
				{
					pair.second->update();
				}
			}
	};
}

typedef fw::System System;