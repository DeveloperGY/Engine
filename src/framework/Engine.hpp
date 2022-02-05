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
			 * @param width 
			 * @param height 
			 * @param key 
			 * @param filepath 
			 */
			static void addTexture(unsigned int width, unsigned int height, std::string key, std::string filepath) {asset_man.addTexture(width, height, key, filepath);}
			
			/**
			 * @brief Retrieves a texture from the asset manager
			 * 
			 * @param key 
			 * @return sf::Texture& 
			 */
			static sf::Texture& getTexture(std::string key) {return asset_man.getTexture(key);}
	};
}

namespace fw
{
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
			std::string texture = "";
	};


	//Systems
	
	class Renderer: public fw::System
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
				sprite.setTexture(fw::Engine::getTexture(s.texture));
				fw::Engine::draw(sprite);

				return;
			}
	};
}

typedef fw::Transform Transform;
typedef fw::Sprite Sprite;
typedef fw::Renderer Renderer;