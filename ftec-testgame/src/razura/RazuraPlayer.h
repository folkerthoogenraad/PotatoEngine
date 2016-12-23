#pragma once

#include "scene/Entity.h"

namespace ftec {

	class RazuraPlayer : public Entity {
	public:
		virtual void onStart();
		virtual void onEnd();

		virtual void update();
		virtual void render3D();
	};
}