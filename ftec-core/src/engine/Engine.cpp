#include "Engine.h"
#include "Time.h"
#include "Input.h"
#include "graphics/Graphics.h"

namespace ftec {

	std::shared_ptr<Scene> Engine::currentScene = nullptr;
	std::unique_ptr<Window> Engine::window = nullptr;
	std::unique_ptr<ResourceManager> Engine::manager = nullptr;

	static void initGL();
	
	void Engine::init()
	{
		LOG("Loading GLFW...");
		//Initialize GLFW
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}
		LOG("GLFW Loaded.");

		//Create context and stuff
		window = std::make_unique<Window>("PotatoEngine", 1280, 720, false);

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

	void Engine::create(std::unique_ptr<Game> g)
	{
		Game &game = *g;
		init();

		game.init();
		
		double previousTime = glfwGetTime();

		//Start running the shit out of this game
		while (!Engine::getWindow().isCloseRequested()) {

			Input::reset();

			getWindow().poll();

			double currentTime = glfwGetTime();
			Time::deltaTime = previousTime - currentTime;
			Time::runTime += Time::deltaTime;
			Time::calculateSinCosTime();

			previousTime = currentTime;

			game.update();

			if (getScene())
				getScene()->update();

			//Begin the full rendering pipeline
			Graphics::begin();

			game.render();

			if (getScene()) {
				getScene()->render();
			}

			//End the rendering pipeline and draw to the screen :D
			Graphics::end();
			

			getWindow().swap();
		}
		
		game.destroy();
		g.reset();

		destroy();
	}

	static void initGL() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		
		glClearColor(.2f, .4f, .8f, 1.f);
		//glClearColor(.0f, .0f, .0f, 1.f);
		//glClearColor(132.f / 255.f, 119.f / 255.f, 106.f / 255.f, 1.f);
	}
}
