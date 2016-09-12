#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Camera.h"

namespace ftec {
	struct StaticGeometry {
		vec3 position;
		Material material;

		std::shared_ptr<Mesh> mesh;
	};

	class Scene {
	public:
		Camera m_Camera;
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

		void addMesh(const vec3 &position, std::shared_ptr<Mesh> mesh, const Material &material);
		
	};

}