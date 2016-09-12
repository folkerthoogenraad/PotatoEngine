#include "Scene.h"

namespace ftec {

	Scene::Scene()
		: m_Camera(60, 4.f / 3.f, 0.1f, 1000.f)
	{

	}

	void Scene::update()
	{
		for (auto i = m_Entities.begin(); i != m_Entities.end(); i++) {
			auto obj = *i;
			obj->update();
		}
	}
	void Scene::render()
	{
		for (auto i = m_Entities.begin(); i != m_Entities.end(); i++) {
			auto obj = *i;
			obj->render();
		}
	}
	void Scene::addEntity(std::shared_ptr<Entity> entity)
	{
		m_Entities.push_back(entity);
	}

	void Scene::removeEntity(std::shared_ptr<Entity> entity)
	{
		//TODO
	}

}
