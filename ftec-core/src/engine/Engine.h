#pragma once

#include "graphics/GL.h"

#define FREEIMAGE_LIB

#include "FreeImage.h"
#include "logger/log.h"

#include <memory>
#include "graphics/Window.h"
#include "scene/Scene.h"
#include "resources/ResourceManager.h"
#include "Game.h"

namespace ftec {

	class Engine {
	private:
		
		static std::shared_ptr<Scene> currentScene;
		static std::unique_ptr<ResourceManager> manager;
		static std::unique_ptr<Window> window;
	public:
		static void init();
		static void destroy();

	public:
		static void create(std::unique_ptr<Game> g);

		static inline std::shared_ptr<Scene> getScene() { return currentScene; };
		static inline void setScene(std::shared_ptr<Scene> scene) { currentScene = scene; };

		static inline Window& getWindow() { return *window; }

		static inline ResourceManager& getResourceManager() { 
			return *manager;
		}
	};
}