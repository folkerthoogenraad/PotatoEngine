#pragma once

#include "math/vec3.h"

namespace ftec {
	class Entity {
	protected:
		vec3 m_Position;
	public:
		virtual void update();
		virtual void render();
	};
}

