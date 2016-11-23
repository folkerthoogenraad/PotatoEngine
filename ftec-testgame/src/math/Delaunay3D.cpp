#include "Delaunay3D.h"

#include "math/sphere.h"
#include "math/triangle3.h"
#include "math/mat4.h"
#include "math/tetrahedron.h"

#include "logger/log.h"
#include <map>

namespace ftec {

	Delaunay3D::Delaunay3D(std::vector<vec3f> points)
	{
		triangulate(std::move(points));
	}

	void Delaunay3D::triangulate(std::vector<vec3f> points)
	{
		m_Vertices.clear();

		vec3f mn, mx;

		//Find the bounding box
		for (auto &p : points) {
			mn.x = min(p.x, mn.x);
			mn.y = min(p.y, mn.y);
			mn.z = min(p.z, mn.z);

			mx.x = max(p.x, mx.x);
			mx.y = max(p.y, mx.y);
			mx.z = max(p.z, mx.z);

			m_Vertices.push_back({ std::move(p), false, false});
		}

		m_Tetrahedrons.clear();
		m_HullTriangles.clear();

		m_BoundingBox = boxf(mn, mx);
		spheref bSphere = m_BoundingBox.boundingSphere();

		//Make a tetrahedron around the bounding sphere (which is about ~6 per unit)
		tetrahedronf superTetrahedron = tetrahedronf::unitTetrahedron().transform(
			mat4::translation(bSphere.center) * mat4::scale(vec3f(bSphere.radius * 6, bSphere.radius * 6, bSphere.radius * 6))
		);

		//Push the tetrahedron vertices
		m_Vertices.push_back({ superTetrahedron.a, false, false });
		m_Vertices.push_back({ superTetrahedron.b, false, false });
		m_Vertices.push_back({ superTetrahedron.c, false, false });
		m_Vertices.push_back({ superTetrahedron.d, false, false });

		//Create the ref for the super triangle
		TetrahedronRef superTetrahedronRef = {
			(int)m_Vertices.size() - 1 ,
			(int)m_Vertices.size() - 2 ,
			(int)m_Vertices.size() - 3 ,
			(int)m_Vertices.size() - 4 };

		//Push the ref
		m_Tetrahedrons.push_back(superTetrahedronRef);
	
		//Loop through all the vertices
		for (int i = 0; i < m_Vertices.size() - 4; i++) { //Ignore the last 4, because they are already processed by the super tetrahedron
			if (i % 100 == 0 && i != 0) {
				LOG("Delaunay is at " << i << "/" << m_Vertices.size());
			}

			const vec3f &v = m_Vertices[i].m_Vertex;

			std::vector<TetrahedronRef> badTetrahedrons;

			//Resulting polygon
			std::map<TriangleRef, int> polygon;

			//Find all the bad tetrahedra
			for (auto &t : m_Tetrahedrons) {
				tetrahedronf tr = tetrahedronf(
					m_Vertices[t.a].m_Vertex,
					m_Vertices[t.b].m_Vertex,
					m_Vertices[t.c].m_Vertex,
					m_Vertices[t.d].m_Vertex
				);

				tetrahedronf oriented = tr.clone().orient();

				auto addTetrahedron = [&t, &polygon, &badTetrahedrons]() {
					badTetrahedrons.push_back(t);

					//If the int is > 1, its a shared edge
					polygon[{ t.a, t.b, t.c}]++;
					polygon[{ t.a, t.b, t.d}]++;
					polygon[{ t.a, t.c, t.d}]++;
					polygon[{ t.b, t.c, t.d}]++;
				};

				int sharedSuperCount = 0;
				{
					if (superTetrahedronRef.contains(t.a))
						sharedSuperCount++;
					if (superTetrahedronRef.contains(t.b))
						sharedSuperCount++;
					if (superTetrahedronRef.contains(t.c))
						sharedSuperCount++;
					if (superTetrahedronRef.contains(t.d))
						sharedSuperCount++;
				}

				//All sharing verts, always add
				if (sharedSuperCount == 4)
					addTetrahedron();

				//Only when there is a triangle there
				else if (sharedSuperCount == 3) {
					triangle3f bdc = tr.trianglebdc();

					if (bdc.distanceFrom(tr.a) > 0)
						bdc.flip();

					bdc.translate(tr.a - tr.b);

					//If its behind the current plane
					if (bdc.distanceFrom(v) >= 0) {
						addTetrahedron();
					}
				}

				//Create plane from two lines
				else if (sharedSuperCount == 2) {
					vec3f normal = vec3f::cross(tr.b - tr.a, tr.d - tr.c);

					if (normal.magnitude() > 0) {
						//Flip if needed
						if (vec3f::dot(normal, tr.c - tr.a) < 0)
							normal = -normal;

						//Add if its in the direction of the super triangle
						if (vec3f::dot(normal, v - tr.a) >= 0)
							addTetrahedron();
					}

				}

				//Use the abc triangle
				else if (sharedSuperCount == 1) {
					triangle3f abc = tr.triangleabc();

					if (abc.distanceFrom(tr.d) > 0)
						abc.flip();

					//If its behind the current plane
					if (abc.distanceFrom(v) <= 0) {
						addTetrahedron();
					}
				}

				//Check if the circumsphere contains this
				else if (contains(tr.circumsphere(), v)) {
					addTetrahedron();
				}
			}

			//Remove all the bad tetrahedra
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
				//Create it only if the triangle is not shared with any other triangle
				if (e.second == 1) {
					m_Tetrahedrons.push_back({
						e.first.a, e.first.b, e.first.c, i
					});
				}
			}
		}

		for (auto &t : m_Tetrahedrons) {
			if (superTetrahedronRef.contains(t.a) || superTetrahedronRef.contains(t.b) || superTetrahedronRef.contains(t.c) || superTetrahedronRef.contains(t.d)) {
				m_Vertices[t.a].m_Hull = true;
				m_Vertices[t.b].m_Hull = true;
				m_Vertices[t.c].m_Hull = true;
				m_Vertices[t.d].m_Hull = true;
			}

			//TODO this check can be done a lot cheaper
			//If it contains only ONE super triangle ref
			if (!superTetrahedronRef.contains(t.a) && !superTetrahedronRef.contains(t.b) && !superTetrahedronRef.contains(t.c) && superTetrahedronRef.contains(t.d)) {
				m_HullTriangles.push_back({ t.a, t.b, t.c });
			}
		}
		
		m_Tetrahedrons.erase(std::remove_if(m_Tetrahedrons.begin(), m_Tetrahedrons.end(),
			[&superTetrahedronRef](TetrahedronRef &t) {
			return superTetrahedronRef.contains(t.a) || superTetrahedronRef.contains(t.b) || superTetrahedronRef.contains(t.c) || superTetrahedronRef.contains(t.d);
		}), m_Tetrahedrons.end());

		for (int i = 0; i < 4; i++)
			m_Vertices.pop_back();
	}


	
}
