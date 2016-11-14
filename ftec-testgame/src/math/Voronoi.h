#pragma once

#include <vector>
#include <set>
#include <map>
#include "math/vec2.h"

namespace ftec {
	class Voronoi {
		std::vector<vec2f> m_Points;

		//The edge indices
		std::vector<std::set<int>> m_Edges;

	public:
		Voronoi(std::vector<vec2f> points);
	
		const vec2f &getPoint(int index) const;
		int getPointCount() const;

		const std::set<int> &getNeighbours(int index);
	
	public:
		void addNeighbour(int from, int to);
	};
}