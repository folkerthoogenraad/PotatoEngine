#include "Delaunay3D.h"
#include "math/tetrahedron.h"
#include <map>

namespace ftec {

	Delaunay3D::Delaunay3D(std::vector<vec3f> points)
	{
		triangulate(std::move(points));
	}

	void Delaunay3D::triangulate(std::vector<vec3f> points)
	{
		m_Vertices = points;
		m_Tetrahedrons.clear();

		//TODO figure this out at runtime obviously
		m_BoundingBox = boxf(vec3f(-1,-1,-1), vec3f(1,1,1));
		spheref bSphere = m_BoundingBox.boundingSphere();

		tetrahedronf superTetrahedron = tetrahedronf::unitTetrahedron().multiplied(
			mat4::translation(bSphere.center) * mat4::scale(vec3f(bSphere.radius * 6, bSphere.radius * 6, bSphere.radius * 6))
		);

		m_Vertices.push_back(superTetrahedron.a);
		m_Vertices.push_back(superTetrahedron.b);
		m_Vertices.push_back(superTetrahedron.c);
		m_Vertices.push_back(superTetrahedron.d);

		m_Tetrahedrons.push_back({
			(int)m_Vertices.size() - 1 ,
			(int)m_Vertices.size() - 2 ,
			(int)m_Vertices.size() - 3 ,
			(int)m_Vertices.size() - 4 });
	
		for (int i = 0; i < m_Vertices.size() - 4; i++) { //Ignore the last few vertices
			const vec3f &v = m_Vertices[i];

			std::vector<TetrahedronRef> badTetrahedrons;

			//Resulting polygon
			std::map<TriangleRef, int> polygon;

			//Find all the bad stuff
			for (auto &t : m_Tetrahedrons) {
				tetrahedronf tr = tetrahedronf(
					m_Vertices[t.a],
					m_Vertices[t.b],
					m_Vertices[t.c],
					m_Vertices[t.d]
				);

				if (contains(tr.circumsphere(), v)) {
					badTetrahedrons.push_back(t);

					//If the int is > 1, its a shared edge
					polygon[{ t.a, t.b, t.c}]++;
					polygon[{ t.a, t.b, t.d}]++;
					polygon[{ t.a, t.c, t.d}]++;
					polygon[{ t.b, t.c, t.d}]++;
				}
			}

			//Remove all the bad triagnels
			m_Tetrahedrons.erase(std::remove_if(m_Tetrahedrons.begin(), m_Tetrahedrons.end(),
				[&badTetrahedrons](TetrahedronRef &t) {
				for (auto &tr : badTetrahedrons) {
					if (tr == t)
						return true;
				}
				return false;
			}), m_Tetrahedrons.end());
		
			//Create the polygon
			for (auto &e : polygon) {
				if (e.second == 1) {
					m_Tetrahedrons.push_back({
						e.first.a, e.first.b, e.first.c, i
					});
				}
			}
		}
	}

	bool Delaunay3D::TetrahedronRef::contains(int i)
	{
		return a == i || b == i || c == i || d == i;
	}

	bool Delaunay3D::TetrahedronRef::operator==(const TetrahedronRef & other)
	{
		return a == other.a && b == other.b && c == other.c && d == other.d;
	}

	Delaunay3D::TriangleRef::TriangleRef(int a, int b, int c)
	{
		//DIRTY DIRTY DIRTY
		std::array<int, 3> s{a, b, c};
		std::sort(s.begin(), s.end());
		this->a = s[0];
		this->b = s[1];
		this->c = s[2];
	}

	bool Delaunay3D::TriangleRef::contains(int i)
	{
		return a == i || b == i || c == i;
	}

	bool Delaunay3D::TriangleRef::operator==(const Delaunay3D::TriangleRef & other) const
	{
		return a == other.a && b == other.b && c == other.c;
	}

	bool Delaunay3D::TriangleRef::operator<(const TriangleRef & other) const
	{
		if (a < other.a)
			return true;
		if (a == other.a) {
			if (b < other.b)
				return true;
			if (b == other.b)
				return c < other.c;
		}

		return false;
	}
}
