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
		static inline std::shared_ptr<Scene> getScene() { return currentScene; };
		static inline void setScene(std::shared_ptr<Scene> scene) { currentScene = scene; };

		static inline Window& getWindow() { return *window; }

		static inline ResourceManager& getResourceManager() { 
			return *manager;
		}

		template<typename T>
		static void create()
		{
			init();

			//Scope because game destructor must be called before destroy is called (for resource reasons)
			{
				T game;
				game.init();

				double previousTime = glfwGetTime();

				Engine::getWindow().setVisible(true);

				//Start running the shit out of this game
				while (!Engine::getWindow().isCloseRequested()) {

					Input::reset();

					getWindow().poll();

					double currentTime = glfwGetTime();
					Time::deltaTime = (float)(currentTime - previousTime);
					Time::runTime += Time::deltaTime;
					Time::calculateSinCosTime();

					previousTime = currentTime;

					game.update();
					game.render();

					//TODO don't render stuff like this
					/*if (getScene())
						getScene()->update();

					//Begin the full rendering pipeline
					Graphics::begin();

					game.render();

					if (getScene()) {
						getScene()->render();
					}

					//End the rendering pipeline and draw to the screen :D
					Graphics::end();*/


					getWindow().swap();
				}

				game.destroy();
			}

			destroy();
			
		}
	};
}