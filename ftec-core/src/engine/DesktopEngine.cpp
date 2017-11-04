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
#if 0
		//Load the engine configuration
		EngineConfiguration config;
		config.init(DEFAULT_GLOBAL_CONFIG_FILE);

		LOG("Loading GLFW...");

		//Initialize GLFW
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}

		LOG("GLFW Loaded.");

		//Create the window
		auto window = std::make_unique<Window>("PotatoEngine", 
			config.width, 
			config.height,
			config.fullscreen,
			config.vsync,
			config.msaa);

		auto manager = std::make_unique<ResourceManager>();

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
		Engine::setResourceManager(std::move(manager));
		Engine::setWindow(std::move(window));

		Engine::init();
#endif
	}

	void DesktopEngine::loop(Game& game, std::shared_ptr<EngineContext> context)
	{
		double previousTime = glfwGetTime();
		double second = 0;
		int frames = 0;

		context->getWindow().setVisible(true);

		//Start running the shit out of this game

		//TODO see what part of this we need here, and what we need in the engine class
		while (!context->getWindow().isCloseRequested()) {
			Time::sleep(context->getConfiguration().framesleep);

			std::vector<Event> events;

			context->getWindow().poll(events);
			
			context->getInput().update(events);

			Time &time = context->getTime();

			double currentTime = glfwGetTime();
			time.deltaTime = (float)(currentTime - previousTime);
			time.runTime += time.deltaTime;
			time.calculateSinCosTime();

			second += time.deltaTime;
			if (second > 1) {
				second -= 1;
				LOG("FPS: " << frames);
				frames = 0;
			}

			previousTime = currentTime;
			
			game.update();
			game.render();
			
			
			if (game.shouldSwapBuffers()) {
				context->getWindow().swap();
				frames++;
			}

			// TODO make this less ugly.
			else if (context->getConfiguration().vsync)
				Time::sleep(8.0f / 1000.0f);
			
			//Set the right framerate
			if (!context->getConfiguration().vsync && context->getConfiguration().targetfps > 0) {
				Time::sleep(1.0f / context->getConfiguration().targetfps);
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

	std::shared_ptr<EngineContext> DesktopEngine::createEngineContext()
	{
		std::shared_ptr<EngineContext> context;

		//Load the engine configuration
		EngineConfiguration config;
		config.init(DEFAULT_GLOBAL_CONFIG_FILE);

		LOG("Loading GLFW...");

		// Initialize GLFW
		// TODO check this with multiple windows and contexts
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}

		LOG("GLFW Loaded.");

		//Create the window
		auto window = std::make_unique<Window>("PotatoEngine",
			config.width,
			config.height,
			config.fullscreen,
			config.vsync,
			config.msaa);

		auto manager = std::make_unique<ResourceManager>();

		window->setVisible(true);

		LOG("Loading GLEW...");

		//Initialize extentions
		if (glewInit() != GLEW_OK) {
			//LOG("Failed to init glew");
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

		return std::make_shared<EngineContext>(config, std::move(window), std::move(manager));
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
		glClearColor(1.f, 1.f, 1.f, 1.f);

	}
}
