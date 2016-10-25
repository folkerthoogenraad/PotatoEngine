#pragma once

#include "graphics/GL.h"

#define FREEIMAGE_LIB

#include "FreeImage.h"
#include "logger/log.h"

#include <memory>
#include "graphics/Window.h"
#include "scene/Scene.h"
#include "resources/ResourceManager.h"

#include "Input.h"
#include "Time.h"
#include "graphics/Graphics.h"
#include "Game.h"
#include "threading/PotatoQueue.h"

#include <functional>

struct lua_State;

namespace ftec {

	class Engine {
	private:
		
		static std::shared_ptr<Scene> currentScene;
		static std::unique_ptr<ResourceManager> manager;
		static std::unique_ptr<Window> window;
		static lua_State *L;

		static PotatoQueue<std::function<void()>> queue;

		static void loop(std::function<void()>);
	public:
		static void init(int width, int height, bool fullscreen);
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
			init(1280, 720, false);

			//Scope because game destructor must be called before destroy is called (for resource reasons)
			{
				T game;
				game.init();

				loop([&game](){
					game.update();
					game.render();
				});

				game.destroy();
			}

			destroy();
			
		}

		static void create_lua(std::string config, std::function<void(lua_State*)>);
	};
}