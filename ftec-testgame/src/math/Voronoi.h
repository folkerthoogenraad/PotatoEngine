#pragma once

#include <vector>
#include <set>
#include <map>
#include "math/vec2.h"
#include "math/rect.h"
#include "Delaunay.h"
#include "lego2.h"

namespace ftec {

	class Voronoi {
		std::vector<ConvexVertex> m_Points;
	public:
		std::vector<lego2f> m_Legos;

		//The edge indices
		std::vector<std::set<int>> m_Edges;

		//Bounding box
		rectf m_BoundingBox;
	public:
		Voronoi() {};
		Voronoi(const Delaunay &delaunay);

		void create(const Delaunay &delaunay);

		const vec2f &getPoint(int index) const;
		int getPointCount() const;
		const lego2f &getLego(int index) const;


		bool isOnHull(int index) const { return m_Points[index].m_Hull; }

		const std::set<int> &getNeighbours(int index) const;
		const rectf &getBoundingBox() const { return m_BoundingBox; }
	
	public:
		void addNeighbour(int from, int to);
	};
}