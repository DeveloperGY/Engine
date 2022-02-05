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
		
			/**
			 * @brief Runs the system
			 * 
			 * @param dt 
			 */
			void update(float dt)
			{
				for(Entity e: this->entities)
				{
					this->run(e, dt);
				}
			}

			/**
			 * @brief Clears the entities in the system
			 * 
			 */
			void clear()
			{
				this->entities.clear();
			}

			friend class SystemManager;

		public:
			
			/**
			 * @brief runs the system on a specific entity
			 * 
			 */
			virtual void run(Entity, float) = 0;
	};

	class SystemManager
	{
		private:
		std::unordered_map<std::string, std::shared_ptr<System>> systems;
		std::unordered_map<std::string, fw::Signature> signatures;

		public:

			/**
			 * @brief Initializes the system manager
			 * 
			 */
			void init();

			/**
			 * @brief Registers a system for use
			 * 
			 * @tparam T 
			 */
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
					this->systems.insert({type, std::make_shared<T>()});
					Signature s;
					this->signatures.insert({type, s});
					return;
				}
				return;
			}

			/**
			 * @brief Set the signature of a system
			 * 
			 * @tparam T 
			 * @param s 
			 */
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

			/**
			 * @brief Retrieves the signature of a system
			 * 
			 * @tparam T 
			 * @return Signature& 
			 */
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

			/**
			 * @brief runs all the systems
			 * 
			 */
			void update(float);

			/**
			 * @brief Removes entity from systems
			 * 
			 * @param e 
			 */
			void entityDestroyed(Entity e);

			/**
			 * @brief Updates system entity sets according to the entity signature
			 * 
			 * @param e 
			 * @param s 
			 */
			void entitySignatureChanged(Entity e, Signature s);

			void clear();
	};
}

typedef fw::System System;