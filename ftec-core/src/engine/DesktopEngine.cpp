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

#include "EngineConfiguration.h"


namespace ftec {

	static void initGL();
	
	void DesktopEngine::init()
	{
		//Set the resource manager
		Engine::setResourceManager(std::make_unique<ResourceManager>());

		//Load the engine configuration
		EngineConfiguration::init();

		LOG("Loading GLFW...");

		//Initialize GLFW
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}

		LOG("GLFW Loaded.");

		//Create the window
		auto window = std::make_unique<Window>("PotatoEngine", 
			EngineConfiguration::width, 
			EngineConfiguration::height, 
			EngineConfiguration::fullscreen, 
			EngineConfiguration::vsync, 
			EngineConfiguration::msaa);

		window->setVisible(true);

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

		//Initialize the OpenGL stuff
		initGL();

		//Tell the world how great we are
		LOG("OpenGL " << glGetString(GL_VERSION) << " Loaded.");

		LOG("");

		//Set the window
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
			Time::sleep(EngineConfiguration::framesleep);

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
			
			//Set the right framerate
			if (!EngineConfiguration::vsync && EngineConfiguration::targetfps > 0) {
				Time::sleep(1.0f / EngineConfiguration::targetfps);
			}
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

		//Backface culling //All windings currently are reversed. I hate life
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Clear color settings
		glClearColor(0.f, 0.f, 1.f, 1.f);

	}
}
