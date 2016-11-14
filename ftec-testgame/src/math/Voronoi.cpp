#include "Voronoi.h"

namespace ftec {
	Voronoi::Voronoi(std::vector<vec2f> points)
		: m_Points(std::move(points))
	{
		m_Edges.resize(m_Points.size());
	}

	const vec2f & ftec::Voronoi::getPoint(int index) const
	{
		return m_Points[index];
	}

	int Voronoi::getPointCount() const
	{
		return m_Points.size();
	}

	const std::set<int>& Voronoi::getNeighbours(int index)
	{
		return m_Edges.at(index);
	}

	void Voronoi::addNeighbour(int from, int to)
	{
		m_Edges[from].insert(to);
		m_Edges[to].insert(from);
	}

}
