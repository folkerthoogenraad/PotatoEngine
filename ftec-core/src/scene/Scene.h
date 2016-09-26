#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"

namespace ftec {
	struct StaticGeometry {
		vec3f position;
		Material material;

		std::shared_ptr<Mesh> mesh;
	};

	class Scene {
	public:
		Camera m_Camera;
		Light m_Light;		//Should be an array ofcourse, but that does not matter right now
	private:
		std::vector<std::shared_ptr<Entity>> m_Entities;
		std::vector<StaticGeometry> m_StaticGeometry;
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void update();
		virtual void render();

		void addEntity(std::shared_ptr<Entity> entity);
		void removeEntity(std::shared_ptr<Entity> entity);

		void addMesh(const vec3f &position, std::shared_ptr<Mesh> mesh, const Material &material);
		
	};

}