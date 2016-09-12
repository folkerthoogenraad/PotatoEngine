#include "Scene.h"
#include "graphics/Renderer.h"
#include "engine/Engine.h"

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
		for (auto i = m_StaticGeometry.begin(); i != m_StaticGeometry.end(); i++) {
			StaticGeometry &geometry = *i;
			Renderer::draw(*geometry.mesh, geometry.material, m_Camera, mat4::translation(geometry.position));
			//static void draw(const Mesh &mesh, const Material &material, const Camera &camera, const mat4 &modelMatrix = mat4::identity());
			
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
