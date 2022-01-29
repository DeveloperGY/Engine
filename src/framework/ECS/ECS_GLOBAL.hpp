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

const std::size_t MAX_COMPS = MAX_COMPONENTS;

namespace fw
{
	template <typename T>
	using sPtr = std::shared_ptr<T>;
	
	typedef unsigned int Entity;
	typedef unsigned int ComponentID;
	typedef std::bitset<MAX_COMPS> Signature;

	template <typename T, std::size_t s_size>
	class DynamicSet
	{
		private:
			std::set<T> arr;
			std::size_t size{0};
			std::size_t max_size{s_size};
		
		public:
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

			auto begin()
			{
				return this->arr.begin();
			}

			auto end()
			{
				return this->arr.end();
			}

			auto find(T item)
			{
				return this->arr.find(item);
			}

			bool empty()
			{
				return !this->size;
			}

			void clear()
			{
				this->arr.clear();
				this->size = 0;
				return;
			}

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
			virtual ~IComponentArray() = default;
			virtual void entityDestroyed(Entity) = 0;
			virtual void clear() = 0;
	};

	template <typename T>
	class ComponentArray: public fw::IComponentArray
	{
		private:
			std::array<std::shared_ptr<T>, MAX_ENTITIES> components;
			std::unordered_map<Entity, std::size_t> eToI{};
			std::unordered_map<std::size_t, Entity> iToE{};
			std::size_t size{0};

		public:
			void insert(T& c, Entity e)
			{
				if(this->eToI.bucket_count() == 0)
				{
					std::cout << "ERROR: Bucket Count Error" << std::endl;
					return;
				}
				if((this->eToI.find(e) == this->eToI.end()) && (this->size < (MAX_COMPS-1))) // sigfpe from this->eToI.find(e)
				{
					this->eToI.insert({e, this->size});
					this->iToE.insert({this->size, e});
					std::shared_ptr<T> ptr = std::make_shared<T>(c);
					this->components.at(this->size) = ptr;
					this->size++;
					return;
				}
				else
				{
					std::cerr << "WARNING: Failed to insert component into component array, entity already owns component!" << std::endl;
					return;
				}
			}

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
			
			T& getComponent(Entity e)
			{
				if(this->eToI.find(e) != this->eToI.end())
				{
					return *this->components.at(this->eToI.at(e));
				}
				else
				{
					std::cerr << "ERROR: Failed to retrive component, entity doesnt own component! Exiting..." << std::endl;
					exit(-1);
				}
			}

			void entityDestroyed(Entity e) override
			{
				if(this->eToI.find(e) != this->eToI.end())
				{
					this->remove(e);
				}
				return;
			}

			void clear() override
			{
				this->eToI.clear();
				this->iToE.clear();
				this->size = 0;
			}
	};
}

typedef fw::Entity Entity;