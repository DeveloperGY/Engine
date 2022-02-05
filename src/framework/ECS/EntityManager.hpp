#pragma once

#include "ECS_GLOBAL.hpp"

#include <unordered_map>
#include <queue>

namespace fw
{
	class EntityManager
	{
		private:
			fw::DynamicSet<Entity, MAX_ENTITIES> entities;
			std::unordered_map<Entity, fw::Signature> signatures;
			std::queue<Entity> destroyed_entities;

		public:
			/**
			 * @brief Initializes the entity manager
			 * 
			 */
			void init();

			/**
			 * @brief Creates an entity
			 * 
			 * @return Entity 
			 */
			Entity createEntity();

			/**
			 * @brief Destroys the specified entity if it exists
			 * 
			 */
			void destroyEntity(fw::Entity);

			/**
			 * @brief Destroys all existing entities
			 * 
			 */
			void clear();

			void addComponent(fw::ComponentID, Entity);

			/**
			 * @brief Removes the specified component from the entity's signature
			 * 
			 */
			void removeComponent(fw::ComponentID, Entity);

			/**
			 * @brief Retrieves the signature of the specified entity
			 * 
			 * @return Signature 
			 */
			Signature getSignature(Entity);

			/**
			 * @brief Retrieves the existing entities
			 * 
			 * @return fw::DynamicSet<Entity, MAX_ENTITIES>& 
			 */
			fw::DynamicSet<Entity, MAX_ENTITIES>& getEntities();
	};
}