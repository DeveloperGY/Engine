#include "EntityManager.hpp"

void fw::EntityManager::init()
{
	return;
}

Entity fw::EntityManager::createEntity()
{
	if(!this->destroyed_entities.empty())
	{
		Entity e = this->destroyed_entities.front();
		Signature s;
		this->destroyed_entities.pop();
		this->entities.insert(e);
		this->signatures.insert({e, s});
		return e;
	}
	else
	{
		static Entity id = 0;
		if(id < MAX_ENTITIES)
		{
			Entity e = id++;
			Signature s;
			this->entities.insert(e);
			this->signatures.insert({e, s});
			return e;
		}
		std::cerr << "WARNING: Failed to create Entity, max entities reached!" << std::endl;
		return NULL;
	}
}

void fw::EntityManager::destroyEntity(Entity e)
{
	if(this->entities.find(e) != this->entities.end())
	{
		this->signatures.erase(e);
		this->entities.erase(e);
		this->destroyed_entities.push(e);
	}
}

void fw::EntityManager::clear()
{
	for(Entity e: this->entities)
	{
		this->destroyEntity(e);
	}
	return;
}

void fw::EntityManager::addComponent(ComponentID id, Entity e)
{
	if(this->entities.find(e) != this->entities.end())
	{
		this->signatures.at(e).set(id);
	}
	else
	{
		std::cerr << "WARNING: Failed to add componentID to entity, entity  not living!" << std::endl;
	}
	return;
}

void fw::EntityManager::removeComponent(ComponentID id, Entity e)
{
	if(this->entities.find(e) != this->entities.end())
	{
		this->signatures.at(e).reset(id);
	}
	else
	{
		std::cerr << "WARNING: Failed to remove componentID from entity, entity not living!" << std::endl;
	}
	return;
}

fw::Signature fw::EntityManager::getSignature(Entity e)
{
	if(this->signatures.find(e) == this->signatures.end())
	{
		std::cerr << "ERROR: Failed to retrieve entity signature, entity not created! Exiting..." << std::endl;
		exit(-1);
	}
	else
	{
		return this->signatures.at(e);
	}
}