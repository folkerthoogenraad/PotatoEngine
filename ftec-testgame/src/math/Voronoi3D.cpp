#include "Voronoi3D.h"
#include "Delaunay3D.h"

#include "math/line3.h"

namespace ftec {
	Voronoi3D::Voronoi3D()
	{

	}

	Voronoi3D::Voronoi3D(const Delaunay3D &delaunay)
	{
		create(delaunay);
	}

	void Voronoi3D::create(const Delaunay3D &d)
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
		m_BoundingBox.min -= vec3f(0.1f, 0.1f, 0.1f);
		m_BoundingBox.max += vec3f(0.1f, 0.1f, 0.1f);

		//m_BoundingBox.min = -vec3f(-1, -1, -1);
		//m_BoundingBox.max = -vec3f(1, 1, 1);

		for (int i = 0; i < m_Delaunay.getPointCount(); ++i) {
			lego3f lego;

			lego.setCenter(m_Delaunay.getPoint(i));

			std::vector<planef> planes;

			const auto &ns = this->getNeighbours(i);

			for (auto &n : ns) {
				line3f line(m_Delaunay.getPoint(i), m_Delaunay.getPoint(n));

				planef plane = planef(line.center(), -line.direction());

				planes.push_back(plane);
			}

			vec3f center = m_BoundingBox.center();
			vec3f delta = m_BoundingBox.delta();

			//Boundingbox planes :)
			planes.push_back(planef(center + delta * vec3f(0, 1, 0), vec3f(0, 1, 0)));
			planes.push_back(planef(center + delta * vec3f(0, -1, 0), vec3f(0, 1, 0)));

			planes.push_back(planef(center + delta * vec3f(1, 0, 0), vec3f(1, 0, 0)));
			planes.push_back(planef(center + delta * vec3f(-1, 0, 0), vec3f(1, 0, 0)));

			planes.push_back(planef(center + delta * vec3f(0, 0, 1), vec3f(0, 0, 1)));
			planes.push_back(planef(center + delta * vec3f(0, 0, -1), vec3f(0, 0, 1)));

			lego.create(std::move(planes));

			m_Legos.push_back(lego);
		}

	}

	void Voronoi3D::addNeighbour(int from, int to)
	{
		m_Edges[from].insert(to);
		m_Edges[to].insert(from);
	}
}
