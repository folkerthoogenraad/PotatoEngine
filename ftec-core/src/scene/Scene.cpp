#include "Scene.h"

namespace ftec {

	//Default scene cannot be null (that'll fuck up some references somewhere down the line)
	std::shared_ptr<Scene> Scene::currentScene = nullptr;

	Scene::Scene()
		: m_Camera(60, 4.f / 3.f, 0.1f, 1000.f)
	{

	}

	void Scene::update()
	{

	}
	void Scene::render()
	{

	}
	void Scene::addEntity(std::shared_ptr<Entity> entity)
	{
		entities.push_back(entity);
	}

	void Scene::removeEntity(std::shared_ptr<Entity> entity)
	{
		//TODO
	}
}
