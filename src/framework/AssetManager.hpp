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

			fw::sPtr<sf::Texture> replaceTexture(unsigned int width, unsigned int height);

		public:
			int init();

			void addTexture(unsigned int width, unsigned int height, std::string key, std::string filepath);
			sf::Texture& getTexture(std::string key);
	};
}