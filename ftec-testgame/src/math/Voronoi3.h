#pragma once

#include "math/lego3.h"
#include "math/Cuboid.h"

#include "Delaunay3.h"

#include <vector>
#include <set>

namespace ftec {

	template <typename T>
	class Voronoi3 {
	public:
		std::vector<std::set<int>> m_Edges;
		std::vector<lego3<T>> m_Legos;
		Cuboid<T> m_BoundingBox;
		Delaunay3<T> m_Delaunay;
	public:
		Voronoi3();
		Voronoi3(const Delaunay3<T> &);
	
		void create(const Delaunay3<T> &);

		const std::set<int> &getNeighbours(int index) const { return m_Edges[index];}
		const std::vector<lego3<T>> &getLegos() const { return m_Legos; }
		const Delaunay3<T> &getDelaunay() const { return m_Delaunay; }

	private:
		void addNeighbour(int from, int to);
	};

	typedef Voronoi3<float> Voronoi3f;
	typedef Voronoi3<double> Voronoi3d;
}