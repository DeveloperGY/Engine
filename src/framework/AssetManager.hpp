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
			std::unordered_map<std::string, sf::Texture> textures;
			std::unordered_map<sf::Vector2i, std::shared_ptr<sf::Texture>> replacement_textures;

			sf::Texture& replaceTexture(unsigned int width, unsigned int height);

		public:
			int init();

			void addTexture(std::string key, std::string filepath);
	};
}