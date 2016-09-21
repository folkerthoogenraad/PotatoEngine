#include "Scene.h"
#include "engine/Engine.h"
#include "engine/Time.h"
#include "graphics/Graphics.h"

namespace ftec {

	Scene::Scene()
		: m_Camera(60, Engine::getWindow().getWidth() / Engine::getWindow().getHeight(), 0.1f, 1000.f)
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
		//This should obviously be batched.
		Graphics::enqueueCamera(&m_Camera);

		for (auto i = m_StaticGeometry.begin(); i != m_StaticGeometry.end(); i++) {
			StaticGeometry &geometry = *i;

			Graphics::enqueueMesh(geometry.mesh.get(), &geometry.material, mat4::translation(geometry.position), LAYER_STATIC);
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
		//TODO
	}

	void Scene::addMesh(const vec3 & position, std::shared_ptr<Mesh> mesh, const Material &material)
	{
		StaticGeometry s;
		s.mesh = mesh;
		s.position = position;
		s.material = material;

		m_StaticGeometry.push_back(s);
	}

}
