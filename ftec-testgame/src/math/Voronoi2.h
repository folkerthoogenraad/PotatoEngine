#pragma once

#include <vector>
#include <set>
#include <map>
#include "math/Vector2.h"
#include "math/Rectangle.h"
#include "Delaunay2.h"
#include "lego2.h"

namespace ftec {

	template <typename T>
	class Voronoi2 {
		std::vector<DelaunayVertex<Vector2<T>>> m_Points;
	public:
		std::vector<lego2<T>> m_Legos;

		//The edge indices
		std::vector<std::set<int>> m_Edges;

		//Bounding box
		Rectangle<T> m_BoundingBox;
	public:
		Voronoi2() {};
		Voronoi2(const Delaunay2<T> &delaunay);

		void create(const Delaunay2<T> &delaunay);

		const Vector2<T> &getPoint(int index) const;
		int getPointCount() const;
		const lego2<T> &getLego(int index) const;


		bool isOnHull(int index) const { return m_Points[index].m_Hull; }

		const std::set<int> &getNeighbours(int index) const;
		const Rectangle<T> &getBoundingBox() const { return m_BoundingBox; }
	
	public:
		void addNeighbour(int from, int to);
	};

	typedef Voronoi2<float> Voronoi2f;
	typedef Voronoi2<double> Voronoi2d;
	typedef Voronoi2<int> Voronoi2i;
}