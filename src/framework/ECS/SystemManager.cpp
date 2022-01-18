#include "SystemManager.hpp"

void fw::SystemManager::init()
{
	return;
}

void fw::SystemManager::update()
{
	for(auto& pair: this->systems)
	{
		pair.second->update();
	}
}

void fw::SystemManager::entityDestroyed(Entity e)
{
	for(auto& pair: this->systems)
	{
		pair.second->entities.erase(e);
	}
	return;
}

void fw::SystemManager::entitySignatureChanged(Entity e, Signature s)
{
	for(auto& pair: this->systems)
	{
		if(s != this->signatures.at(pair.first))
		{
			pair.second->entities.erase(e);
		}
	}
	return;
}

void fw::SystemManager::clear()
{
	for(auto& pair: this->systems)
	{
		pair.second->clear();
	}
}