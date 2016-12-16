#pragma once

namespace ftec {

	class Graphics;
	class Graphics2D;
	class Scene;

	class Entity {
	protected:
		Scene *m_Scene;
	public:
		Entity() = default;
		virtual ~Entity() = default;

		virtual void update() {};
		
		virtual void render3D() {};
		virtual void render2D(Graphics2D &graphics) {};

		void setScene(Scene *scene) { m_Scene = scene; }
		Scene *getScene() { return m_Scene; }
	
		friend Scene;
	};
}

