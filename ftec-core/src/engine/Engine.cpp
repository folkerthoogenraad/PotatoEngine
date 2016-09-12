#include "Engine.h"
#include "Time.h"

namespace ftec {

	std::shared_ptr<Scene> Engine::currentScene = nullptr;
	std::unique_ptr<Window> Engine::window = nullptr;
	std::unique_ptr<ResourceManager> Engine::manager = nullptr;

	static void initGL();
	
	void Engine::init()
	{
		//Initialize GLFW
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}

		//Create context and stuff
		window = std::make_unique<Window>("PotatoEngine", 800, 600, false);

		//Initialize extentions
		if (glewInit() != GLEW_OK) {
			TERMINATE("Couldn't init glew!");
		}

		FreeImage_Initialise();

		initGL();

		manager = std::make_unique<ResourceManager>();

		//Tell the world how great we are
		LOG("Libraries loaded.");
		LOG("OpenGL" << glGetString(GL_VERSION));

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

	void Engine::create(std::unique_ptr<Game> g)
	{
		Game &game = *g;
		init();

		game.init();
		
		double previousTime = glfwGetTime();

		//Start running the shit out of this game
		while (!Engine::getWindow().isCloseRequested()) {
			getWindow().poll();

			double currentTime = glfwGetTime();
			Time::deltaTime = previousTime - currentTime;
			Time::runTime += Time::deltaTime;
			Time::calculateSinCosTime();

			previousTime = currentTime;
			
			if (!game.m_PreventClear)
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			game.update();
			
			if(getScene())
				getScene()->update();

			game.render();

			if (getScene())
				getScene()->render();

			getWindow().swap();
		}
		
		game.destroy();
		g.reset();

		destroy();
	}

	static void initGL() {
		LOG("Initialize the OpenGL stuff");
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);

		glClearColor(.2f, .4f, .8f, 1.f);
		//glClearColor(.0f, .0f, .0f, 1.f);
	}
}
