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
			void init();

			Entity createEntity();
			void destroyEntity(fw::Entity);
			void clear();

			void addComponent(fw::ComponentID, Entity);
			void removeComponent(fw::ComponentID, Entity);
			Signature getSignature(Entity);
			fw::DynamicSet<Entity, MAX_ENTITIES>& getEntities();
	};
}