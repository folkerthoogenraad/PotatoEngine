#pragma once

#include "math/vec3.h"
#include "math/box.h"
#include "math/epsilon.h"
#include "math/math.h"
#include "math/collision.h"
#include "math/mat4.h"
#include "math/sphere.h"
#include "math/triangle3.h"
#include "math/tetrahedron.h"

#include "DelaunayVertex.h"

#include <map>
#include <vector>

namespace ftec {

	template <typename T>
	class Delaunay3 {
	private:
		std::vector<DelaunayVertex<vec3<T>>> m_Vertices;
		std::vector<TetrahedronRef> m_Tetrahedrons;
		std::vector<TriangleRef> m_HullTriangles;

		box<T> m_BoundingBox;
	public:
		Delaunay3() {}
		Delaunay3(std::vector<vec3<T>> points) { triangulate(std::move(points));}

		void triangulate(std::vector<vec3<T>> points)
		{
			m_Vertices.clear();

			vec3<T> mn, mx;

			//Find the bounding box
			for (auto &p : points) {
				mn.x = min(p.x, mn.x);
				mn.y = min(p.y, mn.y);
				mn.z = min(p.z, mn.z);

				mx.x = max(p.x, mx.x);
				mx.y = max(p.y, mx.y);
				mx.z = max(p.z, mx.z);

				m_Vertices.push_back({ std::move(p), false, false });
			}

			m_Tetrahedrons.clear();
			m_HullTriangles.clear();

			m_BoundingBox = box<T>(mn, mx);
			sphere<T> bSphere = m_BoundingBox.boudingsphere();

			//Make a tetrahedron around the bounding sphere (which is about ~6 per unit)
			tetrahedron<T> superTetrahedron = tetrahedron<T>::unitTetrahedron().transform(
				mat4<T>::translation(bSphere.center) * mat4<T>::scale(vec3<T>(bSphere.radius * 6, bSphere.radius * 6, bSphere.radius * 6))
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
				const vec3<T> &v = m_Vertices[i].m_Vertex;

				std::vector<TetrahedronRef> badTetrahedrons;

				//Resulting polygon
				std::map<TriangleRef, int> polygon;

				//Find all the bad tetrahedra
				for (auto &t : m_Tetrahedrons) {
					tetrahedron<T> tr = tetrahedron<T>(
						m_Vertices[t.a].m_Vertex,
						m_Vertices[t.b].m_Vertex,
						m_Vertices[t.c].m_Vertex,
						m_Vertices[t.d].m_Vertex
					);

					tetrahedron<T> oriented = tr.clone().orient();

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
						triangle3<T> bdc = tr.trianglebdc();

						if (bdc.distanceFrom(tr.a) > 0)
							bdc.flip();

						bdc.translate(tr.a - tr.b);

						//If its behind the current plane
						if (bdc.distanceFrom(v) >= EPSILON) {
							addTetrahedron();
						}
					}

					//Create plane from two lines
					else if (sharedSuperCount == 2) {
						vec3<T> normal = vec3<T>::cross(tr.b - tr.a, tr.d - tr.c);

						if (normal.magnitude() > 0) {
							//Flip if needed
							if (vec3<T>::dot(normal, tr.c - tr.a) < 0)
								normal = -normal;

							//Add if its in the direction of the super triangle
							if (vec3<T>::dot(normal, v - tr.a) >= EPSILON)
								addTetrahedron();
						}

					}

					//Use the abc triangle
					else if (sharedSuperCount == 1) {
						triangle3<T> abc = tr.triangleabc();

						if (abc.distanceFrom(tr.d) > 0)
							abc.flip();

						//If its behind the current plane
						if (abc.distanceFrom(v) <= -EPSILON) {
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

		int getPointCount() const { return (int) m_Vertices.size(); };
		const vec3<T> &getPoint(int index) const { return m_Vertices[index].m_Vertex; }
		bool isHull(int index) const { return m_Vertices[index].m_Hull; }

		int getTetraHedronCount() const { return (int) m_Tetrahedrons.size(); }
		const TetrahedronRef &getTetraHedronRef(int index) const { return m_Tetrahedrons[index]; }

		int getHullTriangleCount() const { return (int) m_HullTriangles.size(); }
		const TriangleRef &getHullTriangleRef(int index) const { return m_HullTriangles[index]; }

		const box<T> &getBoundingBox() const { return m_BoundingBox; }
	};

	typedef Delaunay3<float> Delaunay3f;
	typedef Delaunay3<double> Delaunay3d;
	typedef Delaunay3<int> Delaunay3i;
}