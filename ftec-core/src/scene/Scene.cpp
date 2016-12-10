#include "Scene.h"

#include "engine/Engine.h"

#include "graphics/Window.h"
#include "graphics/Graphics.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"
#include "graphics/Renderer.h"

#include "Entity.h"

namespace ftec {

	Scene::Scene()
	{
		//Not sure if we want to have this, but whatever
		m_Cameras.push_back(Camera::perspective(60, Engine::getWindow().getWidth() / Engine::getWindow().getHeight(), 0.1f, 1000.f));
		m_Lights.push_back(Light());
	}

	void Scene::update()
	{
		for (int i = 0; i < m_Entities.size(); ++i) {
			m_Entities[i]->update();
		}
	}
	void Scene::render()
	{
		for (auto &c : m_Cameras)
		{
			Graphics::enqueueCamera(&c);
		}

		for (auto &l : m_Lights)
		{
			Graphics::enqueueLight(&l);
		}

		for (auto i = m_StaticGeometry.begin(); i != m_StaticGeometry.end(); i++) {
			StaticGeometry &geometry = *i;

			Graphics::enqueueMesh(geometry.mesh.get(), geometry.material.get(), Matrix4f::translation(geometry.position), LAYER_STATIC);
		}

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

	}

	void Scene::addMesh(const Vector3f & position, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	{
		StaticGeometry s;

		s.mesh = mesh;
		s.position = position;
		s.material = material;

		m_StaticGeometry.push_back(s);
	}

}
