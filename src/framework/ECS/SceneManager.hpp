#pragma once

#include "ECS_GLOBAL.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

namespace fw
{
	class Scene
	{
		private:
			bool load_set = false;
			std::function<void()> load;

			std::string name;

			void setLoad(std::function<void()> p_onLoad)
			{
				this->load = p_onLoad;
				this->load_set = true;
				return;
			}

			friend class SceneManager;
	};

	class SceneManager
	{
		private:
			fw::EntityManager entity_man;
			fw::ComponentManager component_man;
			fw::SystemManager system_man;

			std::string current_scene;

			std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;

		public:
			void init();

			void createScene(std::string name);
			void loadScene(std::string name);
			void setLoadFunc(std::function<void()> p_load, std::string name);

			Entity createEntity();
			void destroyEntity(Entity e);

			template <typename T>
			void  registerComponent()
			{
				this->component_man.registerComponent<T>();
				return;
			}

			template <typename T>
			void addComponent(Entity e)
			{
				this->component_man.addComponent<T>(e);
				this->entity_man.addComponent(this->component_man.getComponentID<T>(), e);
				this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
				return;
			}

			template <typename T>
			void removeComponent(Entity e)
			{
				this->component_man.removeComponent<T>(e);
				this->entity_man.removeComponent(this->component_man.getComponentID<T>(), e);
				this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
				return;
			}

			template <typename T>
			T& getComponent(Entity e)
			{
				return this->component_man.getComponent<T>(e);
			}

			template <typename T>
			void registerSystem()
			{
				this->system_man.registerSystem<T>();
				for(auto& e: this->entity_man.getEntities())
				{
					this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
				}
				return;
			}

			template <typename T, typename Sys>
			void addSystemRequirement()
			{
				fw::Signature sysSig = this->system_man.getSignature<Sys>();

				sysSig.set(this->component_man.getComponentID<T>(), true);

				this->system_man.setSignature<Sys>(sysSig);

				return;
			}

			template <typename T, typename Sys>
			void removeSystemRequirement()
			{
				fw::Signature sysSig = this->system_man.getSignature<Sys>();

				sysSig.set(this->component_man.getComponentID<T>(), false);

				this->system_man.setSignature<Sys>(sysSig);

				return;
			}

			void update(float);
	};
}