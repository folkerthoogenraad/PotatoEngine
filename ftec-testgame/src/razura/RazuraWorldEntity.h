#pragma once

#include "scene/Entity.h"

namespace ftec {

	class RazuraWorldEntity : public Entity {
	public:
		virtual void onStart();
		virtual void onEnd();

		virtual void update();
		virtual void render3D();
	};

}