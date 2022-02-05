#include "AssetManager.hpp"

int fw::AssetManager::init()
{
	return 1;
}

fw::sPtr<sf::Texture> fw::AssetManager::replaceTexture(unsigned int width, unsigned int height)
{
	std::string aspect = std::to_string(width) + "x" + std::to_string(height);
	
	if(this->replacement_textures.find(aspect) != this->replacement_textures.end())
	{
		return this->replacement_textures.at(aspect);
	}
	else
	{
		sf::Image img;
		img.create(width, height);

		for(unsigned int i = 0; i < height; i++)
		{
			for(unsigned int j = 0; j < width; j++)
			{
				if((i < height/2 && j < width/2) || (i > height/2 && j > height/2))
				{
					img.setPixel(j, i, sf::Color(0, 0, 0 , 255));
				}
				else
				{
					img.setPixel(j, i, sf::Color(255, 0, 255, 255));
				}
			}
		}

		std::shared_ptr<sf::Texture> tex = std::make_shared<sf::Texture>();
		tex->loadFromImage(img);
		this->replacement_textures.insert({aspect, tex});
		return tex;
	}	
}

void fw::AssetManager::addTexture(unsigned int width, unsigned int height, std::string key, std::string filepath)
{
	if(this->textures.find(key) != this->textures.end())
	{
		std::cerr << "WARNING: Failed to add texture, texture with name already exists!" << std::endl;
		return;
	}

	fw::sPtr<sf::Texture> tex = std::make_shared<sf::Texture>();
	if(!tex->loadFromFile(filepath))
	{
		std::cerr << "WARNING: Failed to add texture, file not found." << std::endl;
		tex = this->replaceTexture(width, height);
	}

	this->textures.insert({key, tex});
	return;
}

sf::Texture& fw::AssetManager::getTexture(std::string key)
{
	if(this->textures.find(key) == this->textures.end())
	{
		std::cout << "ERROR: Failed to retrieve texture, texture not found! Exiting..." << std::endl;
		exit(-1);
	}
	else
	{
		return *this->textures.at(key);
	}
}