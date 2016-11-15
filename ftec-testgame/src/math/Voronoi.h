#pragma once

#include <vector>
#include <set>
#include <map>
#include "math/vec2.h"
#include "math/rect.h"

namespace ftec {
	class Delaunay;

	class Voronoi {
		std::vector<vec2f> m_Points;

		//The edge indices
		std::vector<std::set<int>> m_Edges;


		//Bounding box
		rect2f m_BoundingBox;
	public:
		Voronoi() {};
		Voronoi(const Delaunay &delaunay);

		void create(const Delaunay &delaunay);

		const vec2f &getPoint(int index) const;
		int getPointCount() const;

		const std::set<int> &getNeighbours(int index) const;
		const rect2f &getBoundingBox() const { return m_BoundingBox; }
	
	public:
		void addNeighbour(int from, int to);
	};
}