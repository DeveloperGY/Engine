#pragma once

#ifndef MAX_ENTITIES
#define MAX_ENTITIES 5000
#endif

#ifndef MAX_COMPONENTS
#define MAX_COMPONENTS 64
#endif

#include <iostream>
#include <set>
#include <bitset>
#include <array>
#include <unordered_map>
#include <memory>

namespace fw
{
	template <typename T>
	using sPtr = std::shared_ptr<T>;
	
	typedef unsigned int Entity;
	typedef unsigned int ComponentID;
	typedef std::bitset<MAX_COMPONENTS> Signature;

	template <typename T, std::size_t s_size>
	class DynamicSet
	{
		private:
			std::set<T> arr;
			std::size_t size{0};
			std::size_t max_size{s_size};
		
		public:
			/**
			 * @brief Inserts item into the set if there is space
			 * 
			 * @param item 
			 */
			void insert(T item)
			{
				if(this->size < max_size)
				{
					this->arr.insert(item);
					this->size++;
				}
				else
				{
					std::cerr << "WARNING: Failed to insert item, max size reached!" << std::endl;
				}
			}

			/**
			 * @brief Returns iterator to first index in the set
			 * 
			 * @return auto 
			 */
			auto begin()
			{
				return this->arr.begin();
			}

			/**
			 * @brief Returns iterator to the index after the last index of the set
			 * 
			 * @return auto 
			 */
			auto end()
			{
				return this->arr.end();
			}

			/**
			 * @brief Returns an iterator to the specified item
			 * 
			 * @param item 
			 * @return auto 
			 */
			auto find(T item)
			{
				return this->arr.find(item);
			}

			/**
			 * @brief Returns true if the set is empty
			 * 
			 * @return true 
			 * @return false 
			 */
			bool empty()
			{
				return !this->size;
			}

			/**
			 * @brief Clears the set
			 * 
			 */
			void clear()
			{
				this->arr.clear();
				this->size = 0;
				return;
			}

			/**
			 * @brief Erases the specified item from the set
			 * 
			 * @param item 
			 */
			void erase(T item)
			{
				this->arr.erase(item);
				this->size--;
				return;
			}
	};

	class IComponentArray
	{
		private:

		public:
			/**
			 * @brief Destroy the IComponentArray object
			 * 
			 */
			virtual ~IComponentArray() = default;

			/**
			 * @brief Can't call this function
			 * 
			 */
			virtual void entityDestroyed(Entity) = 0;

			/**
			 * @brief Can't call this function
			 * 
			 */
			virtual void clear() = 0;
	};

	template <typename T>
	class ComponentArray: public fw::IComponentArray
	{
		private:
			std::array<T, MAX_ENTITIES> components;
			std::unordered_map<Entity, std::size_t> eToI;
			std::unordered_map<std::size_t, Entity> iToE;
			std::size_t size{0};

		public:
			/**
			 * @brief Inserts a component into the component array
			 * 
			 * @param c 
			 * @param e 
			 */
			void insert(T c, Entity e)
			{
				if(this->eToI.find(e) == this->eToI.end() && this->size < MAX_COMPONENTS-1)
				{
					this->eToI.insert({e, this->size});
					this->iToE.insert({this->size, e});
					this->components.at(this->size) = c;
					this->size++;
					
					return;
				}
				else
				{
					std::cerr << "WARNING: Failed to insert component into component array, entity already owns component!" << std::endl;
					return;
				}
			}

			/**
			 * @brief Removes an entity's component from the component array
			 * 
			 * @param r_e 
			 */
			void remove(Entity r_e)
			{
				if(this->eToI.find(r_e) != this->eToI.end())
				{
					std::size_t r_index = this->eToI.at(r_e);
					Entity l_entity = this->iToE.at(this->size - 1);
					std::size_t l_index = this->size - 1;

					this->components.at(r_index) = this->components.at(l_index);
					
					this->iToE.at(r_index) = l_entity;
					this->iToE.erase(l_index);
					this->eToI.at(l_entity) = r_index;
					this->eToI.erase(r_e);

					this->size--;
				}
				else
				{
					std::cerr << "WARNING: Failed to remove component from component array, entity doesnt own component!" << std::endl;
					return;
				}
			}
			
			/**
			 * @brief Retrieves the component of the specified entity
			 * 
			 * @param e 
			 * @return T& 
			 */
			T& getComponent(Entity e)
			{
				if(this->eToI.find(e) != this->eToI.end())
				{
					return this->components.at(this->eToI.at(e));
				}
				else
				{
					std::cerr << "ERROR: Failed to retrive component, entity doesnt own component! Exiting..." << std::endl;
					exit(-1);
				}
			}

			/**
			 * @brief Removes the component of the specified entity from the component array if it exists
			 * 
			 * @param e 
			 */
			void entityDestroyed(Entity e) override
			{
				if(this->eToI.find(e) != this->eToI.end())
				{
					this->remove(e);
				}
				return;
			}

			/**
			 * @brief Clears the component array
			 * 
			 */
			void clear() override
			{
				this->eToI.clear();
				this->iToE.clear();
				this->size = 0;
			}
	};
}

typedef fw::Entity Entity;