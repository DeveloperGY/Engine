#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>

// TODO: Sound, Music

namespace fw
{
	template <typename T>
	using sPtr = std::shared_ptr<T>;

	class AssetManager
	{
		private:
			std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
			std::unordered_map<std::string, std::shared_ptr<sf::Texture>> replacement_textures;
			std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
			std::unordered_map<std::string, std::string> songs;

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

			/**
			 * @brief Adds a sound to the asset manager
			 * 
			 * @param key 
			 * @param filepath 
			 */
			void addSound(std::string key, std::string filepath);

			/**
			 * @brief Gets a sound from the asset manager
			 * 
			 * @param key 
			 * @return sf::SoundBuffer 
			 */
			sf::SoundBuffer& getSound(std::string key);

			/**
			 * @brief Adds a music file filepath to the asset manager
			 * 
			 * @param key 
			 * @param filepath 
			 */
			void addMusic(std::string key, std::string filepath);

			/**
			 * @brief Gets a music file filepath from the asset manager
			 * 
			 * @param key 
			 * @return std::string 
			 */
			std::string getMusic(std::string key);
	};
}