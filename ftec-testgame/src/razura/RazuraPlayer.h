#pragma once

#include <memory>

#include "math/Vector3.h"
#include "scene/Entity.h"

#include "graphics/Sprite.h"

namespace ftec {

	class RazuraPlayer : public Entity {
		Vector2f m_Position;
		Vector2f m_Motion;
		Sprite m_Sprite;
	public:
		RazuraPlayer(std::shared_ptr<EngineContext> context);
		~RazuraPlayer();

		virtual void onStart() override;
		virtual void onEnd() override;

		virtual void update();
		virtual void render2D(Graphics2D &graphics) override;
	};
}