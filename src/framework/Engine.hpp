#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "ECS/ECS.hpp"

namespace fw
{
	class Engine
	{
		private:
			static fw::Window win;
			static fw::AssetManager asset_man;
			static fw::InputManager input_man;
			static fw::SceneManager scene_man;

			static bool running;

			/**
			 * @brief Exits the engine
			 * 
			 */
			static void exit();

		public:

			/**
			 * @brief Initializes the engine
			 * 
			 * @param p_title 
			 * @param p_width 
			 * @param p_height 
			 * @return int 
			 */
			static int init(std::string p_title = "", unsigned int p_width = 720, unsigned int p_height = 480);
			
			/**
			 * @brief Runs the engine
			 * 
			 */
			static void run();

			/**
			 * @brief Stops the engine and closes the game
			 * 
			 */
			static void stop();
			// Window
			
			/**
			 * @brief Draws to the window
			 * 
			 * @param sprite 
			 */
			static void draw(sf::Drawable& sprite) {win.draw(sprite);}
			
			// Input

			/**
			 * @brief Returns true if teh specified key is pressed
			 * 
			 * @param key 
			 * @return true 
			 * @return false 
			 */
			static bool isKeyPressed(fw::Key::Keys key) {return input_man.isKeyPressed(key);}
			
			/**
			 * @brief Returns true if the specified button is pressed
			 * 
			 * @param button 
			 * @return true 
			 * @return false 
			 */
			static bool isButtonPressed(fw::MouseButton::MouseButtons button) {return input_man.isButtonPressed(button);}

			/**
			 * @brief Retrieves the x position of the mouse relative to the window
			 * 
			 * @return int 
			 */
			static int getMouseX() {return input_man.getMouseX(win.getWindow());}

			/**
			 * @brief Retieves the y position of the mouse relative to the window
			 * 
			 * @return int 
			 */
			static int getMouseY() {return input_man.getMouseY(win.getWindow());}

			/**
			 * @brief Retrives the amount of vertical scroll since the previous frame
			 * 
			 * @return float 
			 */
			static float getMouseScroll() {return win.getScroll();}
			
			// Scenes

			/**
			 * @brief Create a scene
			 * 
			 * @param name 
			 */
			static void createScene(std::string name) {scene_man.createScene(name);}
			
			/**
			 * @brief Loads a scene
			 * 
			 * @param name 
			 */
			static void loadScene(std::string name) {scene_man.loadScene(name);}
			
			/**
			 * @brief Sets a function to be run when a scene is loaded
			 * 
			 * @param p_load 
			 * @param name 
			 */
			static void setSceneLoad(std::function<void()> p_load, std::string name) {scene_man.setLoadFunc(p_load, name);}

			// Entities

			/**
			 * @brief Creates an entity
			 * 
			 * @return fw::Entity 
			 */
			static fw::Entity createEntity() {return scene_man.createEntity();}

			/**
			 * @brief Destroys an entity
			 * 
			 * @param e 
			 */
			static void destroyEntity(Entity e) {scene_man.destroyEntity(e);}

			// Components

			/**
			 * @brief Registers a component for use
			 * 
			 * @tparam T 
			 */
			template <typename T>
			static void registerComponent() {scene_man.registerComponent<T>();}

			/**
			 * @brief Adds a component to an entity
			 * 
			 * @tparam T 
			 * @param e 
			 */
			template <typename T>
			static void addComponent(Entity e) {scene_man.addComponent<T>(e);}

			/**
			 * @brief Removes a component from an entity
			 * 
			 * @tparam T 
			 * @param e 
			 */
			template <typename T>
			static void removeComponent(Entity e) {scene_man.removeComponent<T>(e);}

			/**
			 * @brief Retrives an entity's component
			 * 
			 * @tparam T 
			 * @param e 
			 * @return T& 
			 */
			template <typename T>
			static T& getComponent(Entity e) {return scene_man.getComponent<T>(e);}

			// Systems

			/**
			 * @brief Registers a system for use
			 * 
			 * @tparam T 
			 */
			template <typename T>
			static void registerSystem() {scene_man.registerSystem<T>();}

			/**
			 * @brief Adds a component requirement to a registered system
			 * 
			 * @tparam T 
			 * @tparam Sys 
			 */
			template <typename T, typename Sys>
			static void addSystemRequirement() {scene_man.addSystemRequirement<T, Sys>();}

			/**
			 * @brief Removes a component requirement from a registered system
			 * 
			 * @tparam T 
			 * @tparam Sys 
			 */
			template <typename T, typename Sys>
			static void removeSystemRequirement() {scene_man.removeSystemRequirement<T, Sys>();}

			// Asset Manager

			/**
			 * @brief Adds a texture to the asset manager
			 * 
			 * @param frameWidth 
			 * @param frameHeight 
			 * @param key 
			 * @param filepath 
			 */
			static void addTexture(unsigned int frameWidth, unsigned int frameHeight, std::string key, std::string filepath) {asset_man.addTexture(frameWidth, frameHeight, key, filepath);}
			
			/**
			 * @brief Retrieves a texture from the asset manager
			 * 
			 * @param key 
			 * @return sf::Texture& 
			 */
			static sf::Texture& getTexture(std::string key) {return asset_man.getTexture(key);}
	
			/**
			 * @brief Adds a sound to the asset manager
			 * 
			 * @param key 
			 * @param filepath 
			 */
			static void addSound(std::string key, std::string filepath) {asset_man.addSound(key, filepath);}

			/**
			 * @brief Retrieves a sound from the asset manager
			 * 
			 * @param key 
			 * @return sf::SoundBuffer& 
			 */
			static sf::SoundBuffer& getSound(std::string key) {return asset_man.getSound(key);}

			/**
			 * @brief Adds a song filepath to the asset manager
			 * 
			 * @param key 
			 * @param filepath 
			 */
			static void addMusic(std::string key, std::string filepath) {asset_man.addMusic(key, filepath);}
			
			/**
			 * @brief Retrieves a music file filepath from the asset manager
			 * 
			 * @param key 
			 * @return std::string 
			 */
			static std::string getMusic(std::string key) {return asset_man.getMusic(key);}
	};
}

namespace fw
{
	// Structures

	struct SpriteStructure
	{
		unsigned int frameCount = 1;
		std::string name = "";
		unsigned int srcIndex = 0;
		float frameTime = 1;
	};

	struct SoundStructure
	{
		bool shoudlPlay = false;
		bool playing = false;
		std::string sound = "";
	};

	struct MusicStructure
	{
		bool shouldPlay = false;
		bool playing = false;
		std::string music = "";
	};

	// Components
	
	struct Transform
	{
		public:
			float x{0};
			float y{0};
	};

	struct Sprite
	{
		public:
			std::unordered_map<std::string, SpriteStructure> animations;
			std::string texture = "";
			std::string currentAnimation = "";
			unsigned int frameWidth = 1;
			unsigned int frameHeight = 1;
			unsigned int currentFrame = 0;
			float currentTime = 0;

			/**
			 * @brief Adds an animation to the sprite
			 * 
			 * @param name 
			 * @param index 
			 * @param framecount 
			 * @param frametime 
			 */
			void addAnimation(std::string name, unsigned int index, unsigned int framecount = 1, float frametime = 1)
			{
				if(this->animations.find(name) != this->animations.end())
				{
					std::cerr << "WARNING: Failed to add animation, animation already exists!" << std::endl;
					return;
				}
				fw::SpriteStructure animation;
				animation.frameCount = framecount;
				animation.frameTime = frametime;
				animation.name = name;
				animation.srcIndex = index;
				this->animations.insert({name, animation});
				return;
			}

			/**
			 * @brief Sets the amimation of the sprite
			 * 
			 * @param name 
			 */
			void setAnimation(std::string name)
			{
				if(this->animations.find(name) == this->animations.end())
				{
					std::cerr << "WARNING: Failed to set animation, animation not found!" << std::endl;
					return;
				}
				this->currentFrame = 0;
				this->currentAnimation = name;
				this->currentTime = 0;
				return;
			}
	};

	struct Sound
	{
		public:
			std::unordered_map<std::string, SoundStructure> sounds;
			unsigned int soundCount = 0;
			
			/**
			 * @brief Adds a sound to the sound component
			 * 
			 * @param name 
			 * @param soundKey 
			 */
			void addSound(std::string name, std::string soundKey)
			{
				if(this->sounds.find(name) != this->sounds.end())
				{
					std::cerr << "WARNING: Failed to add sound to sound component!" << std::endl;
					return;
				}
				this->sounds.insert({name, (SoundStructure){false, false, soundKey}});
				this->soundCount++;
				return;
			}
	};

	struct Music
	{
		public:
			std::unordered_map<std::string, MusicStructure> songs;
			unsigned int songCount = 0;
			
			/**
			 * @brief Adds a song to the music component
			 * 
			 * @param name 
			 * @param musicKey 
			 */
			void addMusic(std::string name, std::string musicKey)
			{
				if(this->songs.find(name) != this->songs.end())
				{
					std::cerr << "WARNING: Failed to add song to music component!" << std::endl;
					return;
				}
				MusicStructure s;
				s.music = musicKey;
				s.playing = false;
				s.shouldPlay = false;
				this->songs.insert({name, s});
				this->songCount++;
				return;
			}
	};


	//Systems
	
	class SpriteRenderer: public fw::System
	{
		private:

		public:
			
			/**
			 * @brief Renderes a sprite
			 * 
			 * @param entity 
			 * @param dt 
			 */
			void run(fw::Entity entity, float dt) override
			{
				fw::Transform& t = fw::Engine::getComponent<fw::Transform>(entity);
				fw::Sprite& s = fw::Engine::getComponent<fw::Sprite>(entity);

				sf::Sprite sprite;
				sprite.setPosition(t.x, t.y);
				sprite.setTextureRect(sf::IntRect((s.currentFrame*s.frameWidth), (s.animations.at(s.currentAnimation).srcIndex*s.frameHeight), s.frameWidth, s.frameHeight));
				sprite.setTexture(fw::Engine::getTexture(s.texture));
				// Here 
				fw::Engine::draw(sprite);

				s.currentTime += dt;
				if(s.currentTime >= s.animations.at(s.currentAnimation).frameTime)
				{
					s.currentFrame++;
					s.currentFrame %= s.animations.at(s.currentAnimation).frameCount;
					s.currentTime = 0;
				}

				return;
			}
	};

	class SoundPlayer: public fw::System
	{
		private:
			unsigned int numSounds = 0;
			std::unordered_map<std::shared_ptr<sf::Sound>, float> sounds;
			std::unordered_map<std::shared_ptr<sf::Sound>, SoundStructure*> soundStructs;
			std::set<std::shared_ptr<sf::Sound>> erasables;

		public:

			void update(float dt) override
			{
				for(auto& pair: this->sounds)
				{
					pair.second += dt;

					if(pair.second >= (pair.first->getBuffer()->getDuration().asSeconds()))
					{
						pair.first->stop();
						this->erasables.insert(pair.first);
					}
				}

				for(auto& pair: this->soundStructs)
				{
					if(this->erasables.find(pair.first) != this->erasables.end())
					{
						pair.second->playing = false;
					}
				}

				for(auto& s: this->erasables)
				{
					this->sounds.erase(s);
					this->soundStructs.erase(s);
					this->numSounds--;
				}
				this->erasables.clear();
			}

			void run(fw::Entity entity, float dt) override
			{
				fw::Sound& soundComp = fw::Engine::getComponent<fw::Sound>(entity);
				for(auto& pair: soundComp.sounds)
				{
					auto& sound = pair.second;
					if(sound.shoudlPlay && (this->numSounds < 128))
					{
						std::shared_ptr<sf::Sound> ptr = std::make_shared<sf::Sound>();
						this->sounds.insert({ptr, 0});
						this->soundStructs.insert({ptr, &soundComp.sounds.at(pair.first)});
						ptr->setBuffer(fw::Engine::getSound(sound.sound));
						ptr->play();
						sound.shoudlPlay = false;
						sound.playing = true;
						this->numSounds++;
					}
				}
				return;
			}
	};

	class MusicPlayer: public fw::System
	{
		private:
		std::unordered_map<std::shared_ptr<sf::Music>, float> musicTimes;
		std::unordered_map<std::shared_ptr<sf::Music>, MusicStructure*> musicStructs;
		std::set<std::shared_ptr<sf::Music>> erasables;
		unsigned int numMusic = 0;

		public:
			void update(float dt) override
			{
				for(auto& pair: this->musicTimes)
				{
					pair.second += dt;

					if(pair.second >= (pair.first->getDuration().asSeconds()))
					{
						this->erasables.insert(pair.first);
						pair.first->stop();
					}
				}

				for(auto& pair: this->musicStructs)
				{
					if(this->erasables.find(pair.first) != this->erasables.end())
					{
						pair.second->playing = false;
					}
				}

				for(auto& s: this->erasables)
				{
					this->musicTimes.erase(s);
					this->musicStructs.erase(s);
					this->numMusic--;
				}
				this->erasables.clear();
				return;
			}

			void run(fw::Entity entity, float dt) override
			{
				fw::Music& musicComp = fw::Engine::getComponent<Music>(entity);
				for(auto& pair: musicComp.songs)
				{
					auto& music = pair.second;
					if(music.shouldPlay && (this->numMusic < 128))
					{
						std::shared_ptr<sf::Music> ptr = std::make_shared<sf::Music>();
						if(!ptr->openFromFile(fw::Engine::getMusic(music.music)))
						{
							std::cerr << "WARNING: Music file not found!" << std::endl;
							return;
						}
						this->musicTimes.insert({ptr, 0});
						this->musicStructs.insert({ptr, &pair.second});
						ptr->setVolume(25);
						ptr->play();
						pair.second.shouldPlay = false;
						pair.second.playing = true;
						this->numMusic++;
					}
				}
				return;
			}
	};
}

typedef fw::Transform Transform;
typedef fw::Sprite Sprite;
typedef fw::Sound Sound;
typedef fw::Music Music;

typedef fw::SpriteRenderer SpriteRenderer;
typedef fw::SoundPlayer SoundPlayer;
typedef fw::MusicPlayer MusicPlayer;