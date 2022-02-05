#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>

// TODO: Textures, Sound, Music

namespace fw
{
	template <typename T>
	using sPtr = std::shared_ptr<T>;

	class AssetManager
	{
		private:
			std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
			std::unordered_map<std::string, std::shared_ptr<sf::Texture>> replacement_textures;

			/**
			 * @brief Creates a replacement texture
			 * 
			 * @param width 
			 * @param height 
			 * @return fw::sPtr<sf::Texture> 
			 */
			fw::sPtr<sf::Texture> replaceTexture(unsigned int width, unsigned int height);

		public:
			/**
			 * @brief Initializes the asset manager
			 * 
			 * @return int 
			 */
			int init();

			/**
			 * @brief Adds a texture to the asset manager
			 * 
			 * @param width 
			 * @param height 
			 * @param key 
			 * @param filepath 
			 */
			void addTexture(unsigned int width, unsigned int height, std::string key, std::string filepath);
			
			/**
			 * @brief Gets a texture from the asset manager
			 * 
			 * @param key 
			 * @return sf::Texture& 
			 */
			sf::Texture& getTexture(std::string key);
	};
}