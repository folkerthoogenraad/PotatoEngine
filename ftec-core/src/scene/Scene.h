#pragma once

#include <memory>					//For std::shared_ptr
#include <vector>					//For std::vector

#include "math/Vector3.h"			//For Vector3

namespace ftec {

	class Entity;
	class Mesh;

	struct Material;
	
	class Light;
	class Camera;

	struct StaticGeometry {
		Vector3f position;

		std::shared_ptr<Material> material;
		std::shared_ptr<Mesh> mesh;
	};

	class Scene {
	public:
		std::vector<Camera> m_Cameras;
		std::vector<Light> m_Lights;

		enum SceneMode {
			GRAPHICS_2D,
			GRAPICS_3D,
			GRAPHICS_BOTH
		} m_Mode;

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

		void addMesh(const Vector3f &position, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
		
	};

}