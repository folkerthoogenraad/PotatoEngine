#include "Scene.h"

#include "engine/Engine.h"

#include "graphics/Window.h"
#include "graphics/Graphics.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"
#include "graphics/Renderer.h"

#include "graphics/Graphics2D.h"

#include "math/Vector3.h"

#include "Entity.h"

#include "logger/log.h"


namespace ftec {

	struct StaticGeometry {
		Vector3f position;

		std::shared_ptr<Material> material;
		std::shared_ptr<Mesh> mesh;
	};

	Scene::Scene()
	{
		//Not sure if we want to have this, but whatever
		m_Cameras.push_back(Camera::perspective(60, Engine::getWindow().getWidth() / Engine::getWindow().getHeight(), 0.1f, 1000.f));
		m_Mode = SceneMode::GRAPHICS_3D;
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
		if (m_Mode == SceneMode::GRAPHICS_3D || m_Mode == SceneMode::GRAPHICS_BOTH) {

			Graphics::begin();

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
				auto &obj = *i;
				obj->render3D();
			}

			Graphics::end();
		}

		else
		{
			if (!m_Graphics2D) {
				//NOTE i hate everything about this
				//TODO don't do this here, because this might cause hickups and stuff
				m_Graphics2D = std::make_unique<Graphics2D>();
			}

			m_Graphics2D->begin();
			m_Graphics2D->m_Camera = this->m_Cameras[0]; //Aargh, this is so shit
			for (int i = 0; i < m_Entities.size(); ++i) {
				m_Entities[i]->render2D(*m_Graphics2D);
			}
			m_Graphics2D->end();
		}
	}


	void Scene::addEntity(std::unique_ptr<Entity> entity)
	{
		entity->m_Scene = this;
		m_Entities.push_back(std::move(entity));
	}

	void Scene::addMesh(const Vector3f & position, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	{
		StaticGeometry s;

		s.mesh = mesh;
		s.position = position;
		s.material = material;

		m_StaticGeometry.push_back(s);
	}

	const CollisionWorld & Scene::getCollisionWorld()
	{
		return m_World;
	}

	void Scene::setMode(SceneMode mode)
	{
		m_Mode = mode;
	}

}
