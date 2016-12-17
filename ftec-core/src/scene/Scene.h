#pragma once

#include <memory>					//For std::shared_ptr
#include <vector>					//For std::vector

#include "math/Vector3.h"			//For Vector3

#include "collision/CollisionWorld.h"

namespace ftec {

	class Entity;
	class Mesh;

	struct Material;

	class Graphics2D;
	
	class Light;
	class Camera;

	struct StaticGeometry; // Should be in internal oid

	class Scene {
	public: //Shouldn't be public
		std::vector<Camera> m_Cameras;
		std::vector<Light> m_Lights;

		std::unique_ptr<Graphics2D> m_Graphics2D;
		
		enum SceneMode {
			GRAPHICS_2D,
			GRAPHICS_3D,
			GRAPHICS_BOTH
		};

	private: 
		CollisionWorld m_World;

		std::vector<std::unique_ptr<Entity>> m_Entities;
		std::vector<StaticGeometry> m_StaticGeometry;

		SceneMode m_Mode;
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void update();
		virtual void render();

		Entity					   *addEntity(std::unique_ptr<Entity> entity);
		std::unique_ptr<Entity>		removeEntity(Entity *entity);

		void addMesh(const Vector3f &position, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
		
		const CollisionWorld &getCollisionWorld();

		void setMode(SceneMode mode);
	};

}