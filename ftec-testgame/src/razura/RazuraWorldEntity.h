#pragma once

#include <memory>

#include "scene/Entity.h"

#include "math/Rectangle.h"

namespace ftec {

	class RazuraWorldEntity : public Entity {
	public:
		Rectanglef m_Bounds;
	public:
		RazuraWorldEntity(std::shared_ptr<EngineContext> context, Rectanglef rectangle);
		~RazuraWorldEntity();

		virtual void onStart();
		virtual void onEnd();

		virtual void update();
		virtual void render2D(Graphics2D &graphics);
	};

}