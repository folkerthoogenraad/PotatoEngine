#pragma once

#include "math/Vector3.h"			// For position


namespace ftec {

	class Graphics;
	class Graphics2D;
	class Scene;

	class Entity {
	protected:
		Scene *m_Scene;
		
		Vector3f m_Position;
	public:
		Entity() = default;
		virtual ~Entity() = default;

		virtual void update() {};
		
		virtual void render3D() {};
		virtual void render2D(Graphics2D &graphics) {};
	
		friend Scene;
	};
}

