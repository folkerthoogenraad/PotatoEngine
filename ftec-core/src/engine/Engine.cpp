#include "Engine.h"

#include "Game.h"						//Game

#include "scene/Scene.h"				//Scene
#include "graphics/Window.h"			//Window
#include "resources/ResourceManager.h"	//ResourceManager


namespace ftec {

	//Yes dont you love globals <3
	static std::shared_ptr<Scene> currentScene = nullptr;
	static std::unique_ptr<Window> window = nullptr;
	static std::unique_ptr<ResourceManager> manager = nullptr;

	static void initGL();
	

	void Engine::init()
	{
		
	}

	void Engine::update(Game & game)
	{
		game.update();
		game.render();
	}

	void Engine::destroy()
	{
		currentScene.reset();
		window.reset();
		manager.reset();
	}

	std::shared_ptr<Scene> Engine::getScene()
	{
		return currentScene;
	}

	void Engine::setScene(std::shared_ptr<Scene> scene)
	{
		currentScene = scene;
	}

	Window & Engine::getWindow()
	{
		return *window;
	}

	ResourceManager & Engine::getResourceManager()
	{
		return *manager;
	}

	void Engine::setWindow(std::unique_ptr<Window> win)
	{
		window = std::move(win);
	}

	void Engine::setResourceManager(std::unique_ptr<ResourceManager> res)
	{
		manager = std::move(res);
	}

	
}
