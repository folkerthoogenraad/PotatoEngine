#define FREEIMAGE_LIB

#include "FreeImage.h"
#include "graphics/GL.h"

#include "DesktopEngine.h"

#include "logger/log.h"

#include "Game.h"
#include "Engine.h"

#include "Time.h"
#include "Input.h"

#include "graphics/Window.h"
#include "resources/ResourceManager.h"

namespace ftec {

	static void initGL();

	void DesktopEngine::init()
	{
		LOG("Loading GLFW...");

		//Initialize GLFW
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}

		LOG("GLFW Loaded.");

		//Create context and stuff
		auto window = std::make_unique<Window>("PotatoEngine", 1280, 720, false, true, 4);

		LOG("Loading GLEW...");

		//Initialize extentions
		if (glewInit() != GLEW_OK) {
			TERMINATE("Couldn't init glew!");
		}
		LOG("GLEW Loaded.");

		LOG("Loading FreeImage...");
		FreeImage_Initialise();
		LOG("FreeImage loaded.");

		LOG("");

		LOG("Setting up OpenGL...");

		initGL();

		auto manager = std::make_unique<ResourceManager>();

		//Tell the world how great we are
		LOG("OpenGL " << glGetString(GL_VERSION) << " Loaded.");

		LOG("");

		Engine::setResourceManager(std::move(manager));
		Engine::setWindow(std::move(window));

		Engine::init();
	}

	void DesktopEngine::loop(Game & game)
	{
		double previousTime = glfwGetTime();
		double second = 0;
		int frames = 0;

		Engine::getWindow().setVisible(true);

		//Start running the shit out of this game

		//TODO see what part of this we need here, and what we need in the engine class
		while (!Engine::getWindow().isCloseRequested()) {

			Input::reset();

			Engine::getWindow().poll();

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
			
			Engine::update(game);

			frames++;

			Engine::getWindow().swap();
		}
	}

	void DesktopEngine::destroy()
	{
		//Release these resources first
		Engine::destroy();

		FreeImage_DeInitialise();
		glfwTerminate();
	}

	static void initGL() {
		//Enable depth testing
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		
		//Alpha test
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);

		//Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		//Scissor testing
		glEnable(GL_SCISSOR_TEST);

		//Cubemap interpolations
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		//Backface culling
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		//Clear color settings
		glClearColor(1.f, 1.f, 1.f, 1.f);

	}
}
