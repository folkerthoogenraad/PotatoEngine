#pragma once

#include "graphics/GL.h" //Figure out whether or not this is needed

#include "threading/PotatoQueue.h"
#include <memory>
#include <functional>

namespace ftec {

	class Scene;
	class ResourceManager;
	class Window;
	class Game;

	class Engine {
	private:
		
		static std::shared_ptr<Scene> currentScene;
		static std::unique_ptr<ResourceManager> manager;
		static std::unique_ptr<Window> window;

		static PotatoQueue<std::function<void()>> queue;

		static void loop(Game &game);
	public:
		static void init();
		static void destroy();

	public:
		static inline std::shared_ptr<Scene> getScene() { return currentScene; };
		static inline void setScene(std::shared_ptr<Scene> scene) { currentScene = scene; };

		static inline Window& getWindow() { return *window; }

		static inline ResourceManager& getResourceManager() { 
			return *manager;
		}

		static inline void runOnGraphicsThread(const std::function<void()> &f) {
			queue.push_back(f);
		}

		template<typename T>
		static void create()
		{
			init();

			//Scope because game destructor must be called before destroy is called (for resource reasons)
			{
				T game;
				game.init();

				loop(game);

				game.destroy();
			}

			destroy();
			
		}
	};
}