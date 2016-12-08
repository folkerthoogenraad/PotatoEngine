#include "Voronoi3.h"

#include "math/line3.h"
#include "math/plane.h"

namespace ftec {

	template <typename T>
	Voronoi3<T>::Voronoi3()
	{

	}

	template <typename T>
	Voronoi3<T>::Voronoi3(const Delaunay3<T> &delaunay)
	{
		create(delaunay);
	}

	template <typename T>
	void Voronoi3<T>::create(const Delaunay3<T> &d)
	{
		m_Delaunay = d;
		
		m_Legos.clear();
		m_Edges.clear();
		m_Edges.resize(m_Delaunay.getPointCount());

		m_BoundingBox = m_Delaunay.getBoundingBox();

		for (int i = 0; i < m_Delaunay.getTetraHedronCount(); ++i) {
			const TetrahedronRef &ref = m_Delaunay.getTetraHedronRef(i);

			addNeighbour(ref.a, ref.b);
			addNeighbour(ref.a, ref.c);
			addNeighbour(ref.a, ref.d);

			addNeighbour(ref.b, ref.c);
			addNeighbour(ref.b, ref.d);
			addNeighbour(ref.d, ref.c);
		}

		//Resize bounding box a bit, TODO bounding lego or something
		m_BoundingBox.min -= (T)0.1;
		m_BoundingBox.max += (T)0.1;

		for (int i = 0; i < m_Delaunay.getPointCount(); ++i) {
			lego3<T> lego;

			lego.setCenter(m_Delaunay.getPoint(i));

			std::vector<plane<T>> planes;

			const auto &ns = this->getNeighbours(i);

			for (auto &n : ns) {
				line3<T> line(m_Delaunay.getPoint(i), m_Delaunay.getPoint(n));

				plane<T> p = plane<T>(line.center(), -line.direction());

				planes.push_back(p);
			}

			vec3<T> center = m_BoundingBox.center();
			vec3<T> delta = m_BoundingBox.extends();

			//Boundingbox planes :)
			planes.push_back(plane<T>(center + delta * vec3<T>(0, 1, 0), vec3<T>(0, 1, 0)));
			planes.push_back(plane<T>(center + delta * vec3<T>(0, -1, 0), vec3<T>(0, 1, 0)));

			planes.push_back(plane<T>(center + delta * vec3<T>(1, 0, 0), vec3<T>(1, 0, 0)));
			planes.push_back(plane<T>(center + delta * vec3<T>(-1, 0, 0), vec3<T>(1, 0, 0)));

			planes.push_back(plane<T>(center + delta * vec3<T>(0, 0, 1), vec3<T>(0, 0, 1)));
			planes.push_back(plane<T>(center + delta * vec3<T>(0, 0, -1), vec3<T>(0, 0, 1)));

			lego.create(std::move(planes));

			m_Legos.push_back(lego);
		}

	}

	template <typename T>
	void Voronoi3<T>::addNeighbour(int from, int to)
	{
		m_Edges[from].insert(to);
		m_Edges[to].insert(from);
	}


	template class Voronoi3<float>;
	template class Voronoi3<double>;
}
