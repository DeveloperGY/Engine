#include "AssetManager.hpp"

int fw::AssetManager::init()
{
	return 1;
}

sf::Texture& fw::AssetManager::replaceTexture(unsigned int width, unsigned int height)
{
	if(this->replacement_textures.find(sf::Vector2i(width, height)) != this->replacement_textures.end())
	{
		return *this->replacement_textures.at(sf::Vector2i(width, height));
	}
	else
	{
		sf::Image img;
		img.create(width, height);

		for(unsigned int i; i < height; i++)
		{
			for(unsigned int j; j < width; j++)
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
		this->replacement_textures.insert({sf::Vector2i(width, height), tex});
		return *tex;
	}	
}

void fw::AssetManager::addTexture(std::string key, std::string filepath)
{
	if(this->textures.find(key) != this->textures.end())
	{
		std::cerr << "WARNING: Failed to add texture, texture with name already exists!" << std::endl;
		return;
	}
	else
	{
		// problem: need width and height to make replacement texture but cant get dimensions if file not found
	}
	fw::sPtr<sf::Texture> tex = std::make_shared<sf::Texture>();

}