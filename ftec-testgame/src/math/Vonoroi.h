#pragma once

#include <vector>
#include "math/vec2.h"

namespace ftec {
	class Vonoroi {
		std::vector<vec2f> m_Points;

	public:
		Vonoroi(std::vector<vec2f> points) : m_Points(std::move(points)) {}
	
		const vec2f &getPoint(int index) const;
		int getPointCount() const;
	};
}