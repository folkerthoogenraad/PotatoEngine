#pragma once

#include <memory>				//Unfortunatly, shared_ptrs are basically impossible to fwddeclare

namespace ftec {

	class Scene;

	class ResourceManager;
	class Window;

	class Game;

	class Engine {
	private:

	public:
		static void init();
		static void update(Game &game);
		static void destroy();

	public:
		static Scene *getScene();
		static void setScene(std::unique_ptr<Scene> scene);

		static Window& getWindow();
		static ResourceManager& getResourceManager();

		static void setWindow(std::unique_ptr<Window> win);
		static void setResourceManager(std::unique_ptr<ResourceManager> res);

		
	};
}