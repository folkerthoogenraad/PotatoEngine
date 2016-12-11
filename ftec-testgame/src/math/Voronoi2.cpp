#include "Voronoi2.h"

#include "math/Line2.h"

#include "logger/log.h"

namespace ftec {

	template <typename T>
	Voronoi2<T>::Voronoi2(const Delaunay2<T> &delaunay)
	{
		create(delaunay);
	}


	template <typename T>
	void Voronoi2<T>::create(const Delaunay2<T> & delaunay)
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
		m_BoundingBox.position -= Vector2<T>(1, 1);
		m_BoundingBox.size += Vector2<T>(2, 2);

		for (int i = 0; i < m_Points.size(); ++i) {
			lego2<T> lego;

			lego.setCenter(m_Points[i].m_Vertex);

			std::vector<Line2<T>> edges;

			const auto &ns = this->getNeighbours(i);

			for (auto &n : ns) {
				edges.push_back(
					Line2<T>(m_Points[i].m_Vertex,
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

	template <typename T>
	const Vector2<T> & ftec::Voronoi2<T>::getPoint(int index) const
	{
		return m_Points[index].m_Vertex;
	}

	template <typename T>
	int Voronoi2<T>::getPointCount() const
	{
		return (int) m_Points.size();
	}

	template <typename T>
	const lego2<T> & Voronoi2<T>::getLego(int index) const
	{
		return m_Legos[index];
	}

	template <typename T>
	const std::set<int>& Voronoi2<T>::getNeighbours(int index) const
	{
		return m_Edges.at(index);
	}

	template <typename T>
	void Voronoi2<T>::addNeighbour(int from, int to)
	{
		m_Edges[from].insert(to);
		m_Edges[to].insert(from);
	}


	//Tell the compiler to pretty pretty please compile this 
	template class Voronoi2<float>;
	template class Voronoi2<double>;
}
