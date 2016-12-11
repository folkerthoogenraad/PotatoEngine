#pragma once

#include <memory>					//For std::shared_ptr
#include <vector>					//For std::vector

#include "math/Vector3.h"			//For Vector3


namespace ftec {

	class Entity;
	class Mesh;

	struct Material;

	class Graphics2D;
	
	class Light;
	class Camera;

	struct StaticGeometry; // Should be in internal oid

	class Scene {
	public:
		std::vector<Camera> m_Cameras;
		std::vector<Light> m_Lights;

		std::unique_ptr<Graphics2D> m_Graphics2D;
		//std::unique_ptr<Graphics3D> m_Graphics3D;

		enum SceneMode {
			GRAPHICS_2D,
			GRAPHICS_3D,
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