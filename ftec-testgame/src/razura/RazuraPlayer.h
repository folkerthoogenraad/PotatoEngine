#pragma once

#include <memory>

#include "math/Vector3.h"
#include "scene/Entity.h"

#include "graphics/Sprite.h"

namespace ftec {

	class Mesh;
	struct PBRMaterial;

	class RazuraPlayer : public Entity {
		Vector3f m_Position;
		Sprite m_Sprite;
	public:
		RazuraPlayer();
		~RazuraPlayer();

		virtual void onStart() override;
		virtual void onEnd() override;

		virtual void update() override;
		virtual void render2D(Graphics2D &graphics) override;
	};
}