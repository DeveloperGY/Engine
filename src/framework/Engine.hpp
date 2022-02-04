#pragma once

#include "Window.hpp"
#include "ECS/ECS.hpp"

namespace fw
{
	class Engine
	{
		private:
			static fw::Window win;
			static fw::SceneManager scene_man;

			static bool running;

		public:
			static int init(std::string p_title = "", unsigned int p_width = 720, unsigned int p_height = 480);
			static void run();

			static void exit();

			// TODO: then work on asset manager, then built in systems/components

			// Scenes

			static void createScene(std::string name) {scene_man.createScene(name);}
			static void loadScene(std::string name) {scene_man.loadScene(name);}
			static void setSceneLoad(std::function<void()> p_load, std::string name) {scene_man.setLoadFunc(p_load, name);}

			// Entities

			static fw::Entity createEntity() {return scene_man.createEntity();}
			static void destroyEntity(Entity e) {scene_man.destroyEntity(e);}

			// Components

			template <typename T>
			static void registerComponent() {scene_man.registerComponent<T>();}

			template <typename T>
			static void addComponent(Entity e) {scene_man.addComponent<T>(e);}

			template <typename T>
			static void removeComponent(Entity e) {scene_man.removeComponent<T>(e);}

			template <typename T>
			static T& getComponent(Entity e) {return scene_man.getComponent<T>(e);}

			// Systems

			template <typename T>
			static void registerSystem() {scene_man.registerSystem<T>();}

			template <typename T, typename Sys>
			static void addSystemRequirement() {scene_man.addSystemRequirement<T, Sys>();}

			template <typename T, typename Sys>
			static void removeSystemRequirement() {scene_man.removeSystemRequirement<T, Sys>();}
	};
}

// create systems and stuff