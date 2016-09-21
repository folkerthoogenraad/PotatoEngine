#pragma once

#include "math/vec3.h"

namespace ftec {
	class Entity {
	protected:
		vec3f m_Position;
	public:
		Entity() = default;
		virtual ~Entity() = default;
		virtual void update() = 0;
		virtual void render() = 0;
	};
}

