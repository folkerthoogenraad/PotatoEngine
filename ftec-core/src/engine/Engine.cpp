#include "Engine.h"
#include "Time.h"
#include "Input.h"
#include "graphics/Graphics.h"

#include "lua.hpp"
#include "lua/LuaAPI.h" //For lua api binding

namespace ftec {

	std::shared_ptr<Scene> Engine::currentScene = nullptr;
	std::unique_ptr<Window> Engine::window = nullptr;
	std::unique_ptr<ResourceManager> Engine::manager = nullptr;
	PotatoQueue<std::function<void()>> Engine::queue;
	lua_State *Engine::L;

	static void initGL();
	
	void Engine::loop(std::function<void()> update)
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

			update();

			frames++;

			getWindow().swap();
		}
	}

	void Engine::init(int width, int height, bool fullscreen)
	{
		LOG("Loading GLFW...");
		//Initialize GLFW
		if (!glfwInit()) {
			TERMINATE("Failed to initialize GLFW");
		}
		LOG("GLFW Loaded.");

		//Create context and stuff
		window = std::make_unique<Window>("PotatoEngine", width, height, fullscreen, true, 4);

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

	void Engine::create_lua(std::string config, std::function<void(lua_State*)> callback)
	{
		L = luaL_newstate();
		luaL_openlibs(L);

		int error =
			luaL_loadstring(L, ("require '" + config + "'").c_str()) ||
			lua_pcall(L, 0, 0, 0);

		if (error) {
			LOG_ERROR(lua_tostring(L, -1));
			lua_pop(L, 1);
		}

		//TODO make this into a seperate functnion and stuff
		int width, height;
		bool fullscreen;
		std::string boot;
		std::string updateFunction;

		lua_getglobal(L, "update_function");
		if (!lua_isstring(L, -1))
			LOG("update_function should be a string");

		lua_getglobal(L, "boot_script");
		if (!lua_isstring(L, -1))
			LOG("boot_script should be a string");

		lua_getglobal(L, "width");
		if (!lua_isnumber(L, -1))
			LOG("width should be a int");

		lua_getglobal(L, "height");
		if (!lua_isnumber(L, -1))
			LOG("height should be a int");

		lua_getglobal(L, "fullscreen");
		if (!lua_isboolean(L, -1))
			LOG("fullscreen should be a boolean");

		fullscreen = lua_toboolean(L, -1);
		height = lua_tonumber(L, -2);
		width = lua_tonumber(L, -3);
		boot = lua_tostring(L, -4);
		updateFunction = lua_tostring(L, -5);
		lua_pop(L, 5);

		init(width, height ,fullscreen);

		//Bind the lua api
		lua::bind(L);

		callback(L);

		error =
			luaL_loadstring(L, ("require '" + boot + "'").c_str()) ||
			lua_pcall(L, 0, 0, 0);

		if (error) {
			LOG_ERROR(lua_tostring(L, -1));
			lua_pop(L, 1);
		}

		loop([&updateFunction]() {
			lua_getglobal(L, updateFunction.c_str());
			if (!lua_isfunction(L, -1))
				LOG("update function not a function");

			lua_pcall(L, 0, 0, 0);
		});
		

		destroy();
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

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		//glClearColor(.2f, .4f, .8f, 0.f);
		glClearColor(1.f, 1.f, 1.f, 1.f);
		//glClearColor(.2f, .2f, .2f, 1.f);
		//glClearColor(132.f / 255.f, 119.f / 255.f, 106.f / 255.f, 1.f);
	}
}
