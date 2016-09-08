#include "Scene.h"

namespace ftec {

	//Default scene cannot be null (that'll fuck up some references somewhere down the line)
	std::unique_ptr<Scene> Scene::currentScene = std::make_unique<Scene>();

	Scene::Scene()
		: camera(60, 4.f / 3.f, 0.1f, 1000.f)
	{

	}
	void Scene::update()
	{

	}
}
