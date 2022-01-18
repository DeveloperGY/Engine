#include "SceneManager.hpp"

void fw::SceneManager::init()
{
	this->entity_man.init();
	this->component_man.init();
	this->system_man.init();
	return;
}

fw::Scene& fw::SceneManager::createScene(std::string name)
{
	if(this->scenes.find(name) != this->scenes.end())
	{
		std::cerr << "ERROR: Failed to create scene, scene with name {" << name << "} already exists! Exiting..." << std::endl;
		exit(-1);
	}
	else
	{
		this->scenes.insert({name, std::make_shared<fw::Scene>()});
		this->scenes.at(name)->name = name;
		return *this->scenes.at(name);
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
			return;
		}
	}
}

void fw::SceneManager::loadScene(fw::Scene& scene)
{
	if(!scene.load_set)
	{
		std::cerr << "WARNING: Failed to load scene, scene doesnt have a load fucntion!" << std::endl;
		return;
	}
	else
	{
		this->entity_man.clear();
		this->component_man.clear();
		this->system_man.clear();
		scene.load();
		return;
	}
}