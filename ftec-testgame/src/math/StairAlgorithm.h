#pragma once

#include <vector>
#include "math/math.h"

namespace ftec {

	struct StairArc;

	//Hourglass algorithm?

	struct StairVertex {
		vec2f m_Position;
		float m_Range;
	};

	struct StairAlgorithm {
		std::vector<StairVertex> m_Vertices;

		float getLength();
		vec2f getPosition(float distance);

		StairArc getArc(int index);
		bool isFirst(int index);
		bool isLast(int index);
	};
}