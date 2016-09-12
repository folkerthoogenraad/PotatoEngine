#pragma once

#include "math/vec3.h"

namespace ftec {
	class Entity {
	protected:
		vec3 m_Position;
	public:
		virtual void update() = 0;
		virtual void render() = 0;
	};
}

