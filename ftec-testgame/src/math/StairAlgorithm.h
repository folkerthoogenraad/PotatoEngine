#pragma once

#include <vector>

#include "math/Vector2.h"

namespace ftec {

	struct StairArc;

	//Hourglass algorithm?

	struct StairVertex {
		Vector2f m_Position;
		float m_Range;
	};

	struct StairAlgorithm {
		std::vector<StairVertex> m_Vertices;

		float getLength();
		Vector2f getPosition(float distance);

		StairArc getArc(int index);
		bool isFirst(int index);
		bool isLast(int index);
	};
}