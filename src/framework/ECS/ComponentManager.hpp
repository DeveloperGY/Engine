#pragma once

#include "ECS_GLOBAL.hpp"

#include <typeinfo>
#include <unordered_map>
#include <string>
#include <memory>

namespace fw
{
	class ComponentManager
	{
		template <typename T>
		using sPtr = std::shared_ptr<T>;

		private:
			std::unordered_map<std::string, fw::ComponentID> componentIDs;
			std::unordered_map<std::string, sPtr<fw::IComponentArray>> component_arrays;
			ComponentID currID{0};

			/**
			 * @brief Retrieves the specified component array
			 * 
			 * @tparam T 
			 * @return sPtr<ComponentArray<T>> 
			 */
			template <typename T>
			sPtr<ComponentArray<T>> getComponentArray()
			{
				std::string type = typeid(T).name();
				if(this->component_arrays.find(type) == this->component_arrays.end())
				{
					std::cerr << "ERROR: Failed to retrieve component array, component not registered! Exiting..." << std::endl;
					exit(-1);
				}
				else
				{
					return std::static_pointer_cast<ComponentArray<T>>(this->component_arrays.at(type));
				}
			}

		public:
			/**
			 * @brief Initializes the component manager
			 * 
			 */
			void init();

			/**
			 * @brief Registers a component for use
			 * 
			 * @tparam T 
			 */
			template <typename T>
			void registerComponent()
			{
				std::string type = typeid(T).name();
				if(this->componentIDs.find(type) != this->componentIDs.end())
				{
					std::cerr << "WARNING: Failed to register component, component already registered!" << std::endl;
					return;
				}
				else
				{
					if(this->currID >= MAX_COMPONENTS-1)
					{
						std::cerr << "WARNING: Failed to register component, max components reached!" << std::endl;
						return;
					}

					ComponentID c = currID;
					this->componentIDs.insert({type, c});
					this->component_arrays.insert({type, std::make_shared<ComponentArray<T>>()});
					currID++;
					return;
				}
			}

			/**
			 * @brief Retrieves the specified component id
			 * 
			 * @tparam T 
			 * @return ComponentID 
			 */
			template <typename T>
			ComponentID getComponentID()
			{
				std::string type = typeid(T).name();
				if(this->componentIDs.find(type) == this->componentIDs.end())
				{
					std::cerr << "ERROR: Failed to retrieve component id, component not registered! Exiting..." << std::endl;
					exit(-1);
				}
				else
				{
					return this->componentIDs.at(type);
				}
			}

			/**
			 * @brief Adds a component to an entity
			 * 
			 * @tparam T 
			 * @param e 
			 */
			template <typename T>
			void addComponent(Entity e)
			{
				std::string type = typeid(T).name();
				if(this->componentIDs.find(type) == this->componentIDs.end())
				{
					std::cerr << "WARNING: Failed to add component to entity, component not registered!" << std::endl;
					return;
				}
				else
				{
					T c;
					this->getComponentArray<T>()->insert(c, e);
					return;
				}
			}

			/**
			 * @brief Removes a component from an entity
			 * 
			 * @tparam T 
			 * @param e 
			 */
			template <typename T>
			void removeComponent(Entity e)
			{
				std::string type = typeid(T).name();
				if(this->componentIDs.find(type) == this->componentIDs.end())
				{
					std::cerr << "WARINING: Failed to remove component from entity, component not registed!" << std::endl;
					return;
				}
				else
				{
					this->getComponentArray<T>().remove(e);
					return;
				}
			}

			/**
			 * @brief Retrives the specified entity's component
			 * 
			 * @tparam T 
			 * @param e 
			 * @return T& 
			 */
			template <typename T>
			T& getComponent(Entity e)
			{
				std::string type = typeid(T).name();
				if(this->componentIDs.find(type) == this->componentIDs.end())
				{
					std::cerr << "ERROR: Failed to retrieve component from entity, component not registered! Exiting...";
					exit(-1);
				}
				else
				{
					return this->getComponentArray<T>()->getComponent(e);
				}
			}

			/**
			 * @brief Deletes all components attached to the specified entity
			 * 
			 * @param e 
			 */
			void entityDestroyed(Entity e)
			{
				for(auto& pair: this->component_arrays)
				{
					pair.second->entityDestroyed(e);
				}
				return;
			}

			/**
			 * @brief Erases all components
			 * 
			 */
			void clear()
			{
				for(auto& pair: this->component_arrays)
				{
					pair.second->clear();
				}
			}
	};
}