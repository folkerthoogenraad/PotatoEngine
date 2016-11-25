#include "Voronoi.h"
#include "Delaunay.h"

#include "math/line2.h"

#include "logger/log.h"

namespace ftec {

	Voronoi::Voronoi(const Delaunay & delaunay)
	{
		create(delaunay);
	}

	void Voronoi::create(const Delaunay & delaunay)
	{
		//TODO less memory copying
		m_Points = delaunay.getVertices();
		m_Legos.clear();
		m_Edges.clear();
		m_Edges.resize(m_Points.size());


		for (int i = 0; i < delaunay.getTriangleCount(); ++i) {
			const TriangleRef &ref = delaunay.getTriangleRef(i);

			addNeighbour(ref.a, ref.b);
			addNeighbour(ref.b, ref.c);
			addNeighbour(ref.c, ref.a);
		}

		m_BoundingBox = delaunay.getBoundingBox();
		m_BoundingBox.position -= vec2f(1, 1);
		m_BoundingBox.size += vec2f(2, 2);

		for (int i = 0; i < m_Points.size(); ++i) {
			lego2f lego;

			lego.setCenter(m_Points[i].m_Vertex);

			std::vector<line2f> edges;

			const auto &ns = this->getNeighbours(i);

			for (auto &n : ns) {
				edges.push_back(
					line2f(m_Points[i].m_Vertex,
					m_Points[n].m_Vertex).normal()
				);
			}

			edges.push_back({ m_BoundingBox.topleft(), m_BoundingBox.topright() });
			edges.push_back({ m_BoundingBox.topright(), m_BoundingBox.bottomright() });
			edges.push_back({ m_BoundingBox.bottomright(), m_BoundingBox.bottomleft() });
			edges.push_back({ m_BoundingBox.bottomleft(), m_BoundingBox.topleft() });
			
			lego.create(std::move(edges));

			m_Legos.push_back(lego);
		}

		
	}

	const vec2f & ftec::Voronoi::getPoint(int index) const
	{
		return m_Points[index].m_Vertex;
	}

	int Voronoi::getPointCount() const
	{
		return m_Points.size();
	}

	const lego2f & Voronoi::getLego(int index) const
	{
		return m_Legos[index];
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
