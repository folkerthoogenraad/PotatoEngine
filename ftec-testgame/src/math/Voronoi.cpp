#include "Voronoi.h"
#include "Delaunay.h"

namespace ftec {

	Voronoi::Voronoi(const Delaunay & delaunay)
	{
		create(delaunay);
	}

	void Voronoi::create(const Delaunay & delaunay)
	{
		//TODO less memory copying
		m_Points = delaunay.getPoints();
		m_Edges.clear();
		m_Edges.resize(m_Points.size());


		for (int i = 0; i < delaunay.getTriangleCount(); ++i) {
			const TriangleRef &ref = delaunay.getTriangleRef(i);

			addNeighbour(ref.a, ref.b);
			addNeighbour(ref.b, ref.c);
			addNeighbour(ref.c, ref.a);
		}

		m_BoundingBox = delaunay.getBoundingBox();
	}

	const vec2f & ftec::Voronoi::getPoint(int index) const
	{
		return m_Points[index];
	}

	int Voronoi::getPointCount() const
	{
		return m_Points.size();
	}

	const std::set<int>& Voronoi::getNeighbours(int index) const
	{
		return m_Edges.at(index);
	}

	void Voronoi::addNeighbour(int from, int to)
	{
		m_Edges[from].insert(to);
		m_Edges[to].insert(from);
	}

}
