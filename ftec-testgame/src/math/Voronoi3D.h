#pragma once

#include "math/lego3.h"
#include "math/box.h"

#include "Delaunay3D.h"

#include <vector>
#include <set>

namespace ftec {

	class Voronoi3D {
	public:
		std::vector<std::set<int>> m_Edges;
		std::vector<lego3f> m_Legos;
		boxf m_BoundingBox;
		Delaunay3D m_Delaunay;
	public:
		Voronoi3D();
		Voronoi3D(const Delaunay3D &);
	
		void create(const Delaunay3D &);

		const std::set<int> &getNeighbours(int index) const { return m_Edges[index];}
		const std::vector<lego3f> &getLegos() const { return m_Legos; }
		const Delaunay3D &getDelaunay() const { return m_Delaunay; }

	private:
		void addNeighbour(int from, int to);
	};
}