#include "SceneManager.hpp"

void fw::SceneManager::init()
{
	this->entity_man.init();
	this->component_man.init();
	this->system_man.init();
	return;
}

void fw::SceneManager::createScene(std::string name)
{
	if(this->scenes.find(name) != this->scenes.end())
	{
		std::cerr << "WARNING: Failed to create scene, scene with name \"" << name << "\" already exists!" << std::endl;
		return;
	}
	else
	{
		this->scenes.insert({name, std::make_shared<fw::Scene>()});
		this->scenes.at(name)->name = name;
		return;
	}
}

void fw::SceneManager::loadScene(std::string name)
{
	if(this->scenes.find(name) == this->scenes.end())
	{
		std::cerr << "WARNING: Failed to load scene, scene not found!" << std::endl;
		return;
	}
	else
	{
		if(!this->scenes.at(name)->load_set)
		{
			std::cerr << "WARNING: Failed to load scene, scene doesnt have a load fucntion!" << std::endl;
			return;
		}
		else
		{
			this->entity_man.clear();
			this->component_man.clear();
			this->system_man.clear();
			this->scenes.at(name)->load();
			this->current_scene = name;
			return;
		}
	}
}

void fw::SceneManager::setLoadFunc(std::function<void()> p_load, std::string name)
{
	if(this->scenes.find(name) == this->scenes.end())
	{
		std::cerr << "WARNING: Failed to set the loading function of scene, scene not found!" << std::endl;
		return;
	}
	else
	{
		this->scenes.at(name)->setLoad(p_load);
		return;
	}
}

fw::Entity fw::SceneManager::createEntity()
{
	Entity e = this->entity_man.createEntity();
	this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
	return e;
}

void fw::SceneManager::destroyEntity(Entity e)
{
	this->entity_man.destroyEntity(e);
	this->component_man.entityDestroyed(e);
	this->system_man.entityDestroyed(e);
	return;
}

void fw::SceneManager::update(float dt)
{
	this->system_man.update(dt);
	return;
}