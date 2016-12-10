#pragma once

#include "math/Vector3.h"			// For position

namespace ftec {
	class Entity {
	protected:
		Vector3f m_Position;
	public:
		Entity() = default;
		virtual ~Entity() = default;
		virtual void update() = 0;
		virtual void render() = 0;
	};
}

