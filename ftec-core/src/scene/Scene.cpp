#include "Scene.h"

namespace ftec {

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
