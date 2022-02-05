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

			/**
			 * @brief Sets the loading function that is called when the scene gets loaded
			 * 
			 * @param p_onLoad 
			 */
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
			/**
			 * @brief Initializaes the scene manager
			 * 
			 */
			void init();

			/**
			 * @brief Create a scene
			 * 
			 * @param name 
			 */
			void createScene(std::string name);

			/**
			 * @brief Loads the specified scene
			 * 
			 * @param name 
			 */
			void loadScene(std::string name);

			/**
			 * @brief Sets the loading function of the specified scene
			 * 
			 * @param p_load 
			 * @param name 
			 */
			void setLoadFunc(std::function<void()> p_load, std::string name);

			/**
			 * @brief Creates an entity
			 * 
			 * @return Entity 
			 */
			Entity createEntity();

			/**
			 * @brief Destroys an entity
			 * 
			 * @param e 
			 */
			void destroyEntity(Entity e);

			/**
			 * @brief Registers a component for use
			 * 
			 * @tparam T 
			 */
			template <typename T>
			void  registerComponent()
			{
				this->component_man.registerComponent<T>();
				return;
			}

			/**
			 * @brief Adds a component to the specified entity
			 * 
			 * @tparam T 
			 * @param e 
			 */
			template <typename T>
			void addComponent(Entity e)
			{
				this->component_man.addComponent<T>(e);
				this->entity_man.addComponent(this->component_man.getComponentID<T>(), e);
				this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
				return;
			}

			/**
			 * @brief Removes a component from the specified entity
			 * 
			 * @tparam T 
			 * @param e 
			 */
			template <typename T>
			void removeComponent(Entity e)
			{
				this->component_man.removeComponent<T>(e);
				this->entity_man.removeComponent(this->component_man.getComponentID<T>(), e);
				this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
				return;
			}

			/**
			 * @brief Retrieves a component from the specified entity
			 * 
			 * @tparam T 
			 * @param e 
			 * @return T& 
			 */
			template <typename T>
			T& getComponent(Entity e)
			{
				return this->component_man.getComponent<T>(e);
			}

			/**
			 * @brief Registers a system for use
			 * 
			 * @tparam T 
			 */
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

			/**
			 * @brief Adds a component requirement to the specified system
			 * 
			 * @tparam T 
			 * @tparam Sys 
			 */
			template <typename T, typename Sys>
			void addSystemRequirement()
			{
				fw::Signature sysSig = this->system_man.getSignature<Sys>();

				sysSig.set(this->component_man.getComponentID<T>(), true);

				this->system_man.setSignature<Sys>(sysSig);

				for(auto& e: this->entity_man.getEntities())
				{
					this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
				}

				return;
			}

			/**
			 * @brief Removes a component requirement from a system, there should be no reason to use this function
			 * 
			 * @tparam T 
			 * @tparam Sys 
			 */
			template <typename T, typename Sys>
			void removeSystemRequirement()
			{
				fw::Signature sysSig = this->system_man.getSignature<Sys>();

				sysSig.set(this->component_man.getComponentID<T>(), false);

				this->system_man.setSignature<Sys>(sysSig);

				for(auto& e: this->entity_man.getEntities())
				{
					this->system_man.entitySignatureChanged(e, this->entity_man.getSignature(e));
				}

				return;
			}

			/**
			 * @brief Runs all the systems
			 * 
			 */
			void update(float);
	};
}