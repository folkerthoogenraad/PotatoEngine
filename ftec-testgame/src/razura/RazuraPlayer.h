#pragma once

#include <memory>

#include "math/Vector3.h"
#include "scene/Entity.h"

namespace ftec {

	class Mesh;
	struct PBRMaterial;

	class RazuraPlayer : public Entity {
		Vector3f m_Position;
	public:
		RazuraPlayer();
		~RazuraPlayer();

		virtual void onStart();
		virtual void onEnd();

		virtual void update();
		virtual void render2D(Graphics2D &graphics);
	};
}