#pragma once

#include "math/Triangle2.h"
#include "math/Rectangle.h"

#include "math/math.h"
#include "math/collision.h"
#include "math/Line2.h"
#include "math/Circle.h"

#include "DelaunayVertex.h"

#include <vector>
#include <algorithm>
#include <map>

namespace ftec {

	template <typename T>
	class Delaunay2 {
	private:
		std::vector<DelaunayVertex<Vector2<T>>> m_Vertices;

		std::vector<TriangleRef> m_Triangles;

		Rectangle<T> m_BoundingBox;
	public:
		Delaunay2() {}
		Delaunay2(std::vector<Vector2<T>> points)
		{
			triangulate(std::move(points));
		}

		void triangulate(std::vector<Vector2<T>> points)
		{
			m_Triangles.clear();

			Vector2<T> minPosition = points.front();
			Vector2<T> maxPosition = minPosition;

			for (auto & v : points) {
				minPosition.x = min(v.x, minPosition.x);
				minPosition.y = min(v.y, minPosition.y);

				maxPosition.x = max(v.x, maxPosition.x);
				maxPosition.y = max(v.y, maxPosition.y);

				m_Vertices.push_back({ v, false, false });
			}

			//TODO for the bounding super triangle, i should use a better bounding triangle
			//if the bounding box is very slim, the triangle wont caputure all the points and the thing will fail
			//This is a know issue, should be fixed very very soon (~ish)

			{
				Vector2<T> delta = maxPosition - minPosition;
				m_BoundingBox = Rectangle<T>(minPosition.x, minPosition.y, delta.x, delta.y);
			}

			Vector2<T> delta = maxPosition - minPosition;

			Circle<T> c = m_BoundingBox.boundingCircle();

			m_Vertices.push_back({ c.center + Vector2<T>(0, 2) * c.radius, true, true });
			m_Vertices.push_back({ c.center + Vector2<T>(-2, -1) * c.radius, true, true });
			m_Vertices.push_back({ c.center + Vector2<T>(2, -1) * c.radius, true, true });

			TriangleRef superTriangle((int)m_Vertices.size() - 1, (int)m_Vertices.size() - 2, (int)m_Vertices.size() - 3);

			//bowyer watson super triangle
			m_Triangles.push_back(superTriangle);

			for (int i = 0; i < m_Vertices.size() - 3; i++) { //Ignore the last few vertices
				const Vector2<T> &v = m_Vertices[i].m_Vertex;

				std::vector<TriangleRef> badTriangles;

				//Resulting polygon
				std::map<EdgeRef, int> polygon;

				//Find all bad triangles
				for (auto &t : m_Triangles) {
					//Triangles
					Triangle2<T> triangle = Triangle2<T>(m_Vertices[t.a].m_Vertex, m_Vertices[t.b].m_Vertex, m_Vertices[t.c].m_Vertex);
					Triangle2<T> oriented = triangle.clone().orient();

					//Function to add the triangle, it happens in 4 different scenarios.
					auto addTriangle = [&t, &polygon, &badTriangles]() {
						//If the int is > 1, its a shared edge
						badTriangles.push_back(t);

						polygon[{ t.a, t.b }]++;
						polygon[{ t.b, t.c }]++;
						polygon[{ t.c, t.a }]++;
					};

					//a b c are in order, super triangle are the last 3 vertices
					//We need to count the triangle shares, because the 3 triangle vertices should lie infinitly far away
					//So in order to simulate it, we must do some line detections, instead of the normal stuff
					int sharedSuperCount = 0;
					{
						if (superTriangle.contains(t.c))
							sharedSuperCount += 1;
						if (superTriangle.contains(t.b))
							sharedSuperCount += 1;
						if (superTriangle.contains(t.a))
							sharedSuperCount += 1;
					}

					//If all verts are at super triangle -> always pass
					if (sharedSuperCount == 3)
						addTriangle();

					//If two are at super triangle -> pass when behind line
					else if (sharedSuperCount == 2 && oriented.edgebc().translate(triangle.b - triangle.a).distanceFrom(v) >= 0) {
						addTriangle();
					}

					//If one is at super triangle -> pass when behind line
					else if (sharedSuperCount == 1) {
						Line2<T> ab = triangle.edgeab();
						if (ab.distanceFrom(triangle.c) > 0) {
							ab.flip();
						}

						if (ab.distanceFrom(v) <= 0) {
							addTriangle();
						}
					}

					//Check this last
					else if (contains(triangle.circumcircle(), v)) {
						addTriangle();
					}

				}

				//Remove the badTriangles
				m_Triangles.erase(std::remove_if(m_Triangles.begin(), m_Triangles.end(),
					[&badTriangles](TriangleRef &t) {
					for (auto &tr : badTriangles) {
						if (tr == t)
							return true;
					}
					return false;
				}), m_Triangles.end());

				for (auto &e : polygon) {
					if (e.second == 1) {
						m_Triangles.push_back({
							e.first.a, e.first.b, i
						});
					}
				}
			}

			//Should be one loop, this and the remove_if

			//Count all the connected hull triangles
			for (auto &t : m_Triangles) {
				if (superTriangle.contains(t.a) || superTriangle.contains(t.b) || superTriangle.contains(t.c)) {
					m_Vertices[t.a].m_Hull = true;
					m_Vertices[t.b].m_Hull = true;
					m_Vertices[t.c].m_Hull = true;
				}
			}


			m_Triangles.erase(std::remove_if(m_Triangles.begin(), m_Triangles.end(),
				[&superTriangle](TriangleRef &t) {
				return superTriangle.contains(t.a) || superTriangle.contains(t.b) || superTriangle.contains(t.c);
			}), m_Triangles.end());

			for (int i = 0; i < 3; i++)
				m_Vertices.pop_back();

		}

		int getPointCount() const { return m_Vertices.size(); };
		const Vector2<T> &getPoint(int index) const { return m_Vertices[index].m_Vertex; }
		const std::vector<DelaunayVertex<Vector2<T>>> &getVertices() const { return m_Vertices; }

		int getTriangleCount() const { return (int) m_Triangles.size(); }
		const TriangleRef &getTriangleRef(int index) const { return m_Triangles[index]; }
		Triangle2<T> getTriangle(int index) const
		{
			TriangleRef ref = getTriangleRef(index);

			return Triangle2<T>(
				getPoint(ref.a),
				getPoint(ref.b),
				getPoint(ref.c));
		}

		const Rectangle<T> &getBoundingBox() const { return m_BoundingBox; }
	};

	typedef Delaunay2<float> Delaunay2f;
	typedef Delaunay2<double> Delaunay2d;
	typedef Delaunay2<int> Delaunay2i;
}