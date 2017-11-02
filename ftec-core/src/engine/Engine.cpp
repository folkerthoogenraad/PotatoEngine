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

	void Engine::init()
	{ }

	void Engine::update(Game & game)
	{
		game.update();
		
		// TODO reimplements scenes and shit (maybe on Game level ?)
		//if (getScene())
		//	getScene()->update();
		
		game.render();

		//if (getScene())
		//	getScene()->render();
	}

	void Engine::destroy()
	{
		currentScene.reset();
		window.reset();
		manager.reset();
	}

#if 0
	Scene *Engine::getScene()
	{
		return currentScene.get();
	}

	void Engine::setScene(std::unique_ptr<Scene> scene)
	{
		currentScene = std::move(scene);
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
#endif
	
}
