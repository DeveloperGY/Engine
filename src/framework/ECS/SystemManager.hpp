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
		
			void update(float dt)
			{
				for(Entity e: this->entities)
				{
					this->run(e, dt);
				}
			}

			void clear()
			{
				this->entities.clear();
			}

			friend class SystemManager;

		public:
			virtual void run(Entity, float) = 0;
	};

	class SystemManager
	{
		private:
		std::unordered_map<std::string, std::shared_ptr<System>> systems;
		std::unordered_map<std::string, fw::Signature> signatures;

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
					Signature s;
					this->signatures.insert({type, s});
					return;
				}
				return;
			}

			template <typename T>
			void setSignature(Signature s)
			{
				std::string type = typeid(T).name();
				if(this->systems.find(type) == this->systems.end())
				{
					std::cerr << "WARNING: Failed to set system signature, system not registered!" << std::endl;
					return;
				}
				else
				{
					this->signatures.at(type) = s;
				}
				return;
			}

			template <typename T>
			Signature& getSignature()
			{
				std::string type = typeid(T).name();
				if(this->systems.find(type) == this->systems.end())
				{
					std::cerr << "ERROR: Failed to retrieve system signature, system not registered! Exiting..." << std::endl;
					exit(-1);
				}
				else
				{
					return this->signatures.at(type);
				}
			}

			void update(float);

			void entityDestroyed(Entity e);

			void entitySignatureChanged(Entity e, Signature s);

			void clear();
	};
}

typedef fw::System System;