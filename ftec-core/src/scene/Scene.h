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
	public: //Shouldn't be public
		std::vector<Camera> m_Cameras;
		std::vector<Light> m_Lights;

		std::unique_ptr<Graphics2D> m_Graphics2D;
		//std::unique_ptr<Graphics3D> m_Graphics3D;

		enum SceneMode {
			GRAPHICS_2D,
			GRAPHICS_3D,
			GRAPHICS_BOTH
		};

	private: 
		std::vector<std::unique_ptr<Entity>> m_Entities; //Maybe create a nice entity component system of sorts, but for now, this'll do
		std::vector<StaticGeometry> m_StaticGeometry;

		SceneMode m_Mode;
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void update();
		virtual void render();

		void addEntity(std::unique_ptr<Entity> entity);

		void addMesh(const Vector3f &position, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
		
		void setMode(SceneMode mode);
	};

}