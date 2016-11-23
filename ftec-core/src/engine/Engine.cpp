#define FREEIMAGE_LIB

#include "FreeImage.h"

#include "Engine.h"
#include "Time.h"
#include "Input.h"
#include "graphics/Graphics.h"


#include "logger/log.h"

#include "graphics/Window.h"
#include "scene/Scene.h"
#include "resources/ResourceManager.h"

#include "Input.h"
#include "Time.h"
#include "graphics/Graphics.h"
#include "Game.h"

#include "threading/PotatoQueue.h"

namespace ftec {

	std::shared_ptr<Scene> Engine::currentScene = nullptr;
	std::unique_ptr<Window> Engine::window = nullptr;
	std::unique_ptr<ResourceManager> Engine::manager = nullptr;
	PotatoQueue<std::function<void()>> Engine::queue;

	static void initGL();
	
	void Engine::loop(Game & game)
	{
		double previousTime = glfwGetTime();
		double second = 0;
		int frames = 0;

		Engine::getWindow().setVisible(true);

		//Start running the shit out of this game
		while (!Engine::getWindow().isCloseRequested()) {

			Input::reset();

			getWindow().poll();

			double currentTime = glfwGetTime();
			Time::deltaTime = (float)(currentTime - previousTime);
			Time::runTime += Time::deltaTime;
			Time::calculateSinCosTime();

			second += Time::deltaTime;
			if (second > 1) {
				second -= 1;
				LOG("FPS: " << frames);
				frames = 0;
			}

			previousTime = currentTime;

			while (!queue.empty()) {
				queue.pop_back()();
			}

			game.update();
			game.render();
			frames++;

			getWindow().swap();
		}
	}

	void Engine::init()
	{
		LOG("Loading GLFW...");
		//Initialize GLFW
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}
		LOG("GLFW Loaded.");

		//Create context and stuff
		window = std::make_unique<Window>("PotatoEngine", 1280, 720, false, true, 4);

		LOG("Loading GLEW...");
		//Initialize extentions
		if (glewInit() != GLEW_OK) {
			TERMINATE("Couldn't init glew!");
		}
		LOG("GLEW Loaded.");

		FreeImage_Initialise();

		LOG("Loading OpenGL...");

		initGL();

		manager = std::make_unique<ResourceManager>();

		//Tell the world how great we are
		LOG("OpenGL " << glGetString(GL_VERSION) << " Loaded.");

	}

	void Engine::destroy()
	{
		//Release these resources first
		currentScene.reset();
		window.reset();
		manager.reset();
		FreeImage_DeInitialise();
		glfwTerminate();
	}

	static void initGL() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_SCISSOR_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Reenable for performance reasons, disabled now for other reasons
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		//glClearColor(.2f, .4f, .8f, 0.f);
		//glClearColor(1.f, 1.f, 1.f, 1.f);
		//glClearColor(.2f, .2f, .2f, 1.f);
		glClearColor(.0f, .0f, .0f, 1.f);
		//glClearColor(132.f / 255.f, 119.f / 255.f, 106.f / 255.f, 1.f);
	}
}
