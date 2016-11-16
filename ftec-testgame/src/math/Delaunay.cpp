#include "Delaunay.h"

#include <algorithm>
#include <map>

#include "math/collision.h"
#include "logger/log.h"

namespace ftec {

	Delaunay::Delaunay(std::vector<vec2f> points)
	{
		triangulate(std::move(points));
	}

	void Delaunay::triangulate(std::vector<vec2f> points)
	{
		//TODO same issue, implement solution
		//http://stackoverflow.com/questions/30741459/bowyer-watson-algorithm-how-to-fill-holes-left-by-removing-triangles-with-sup

		m_Triangles.clear();

		vec2f minPosition = points.front();
		vec2f maxPosition = minPosition;

		for (auto & v : points) {
			minPosition.x = min(v.x, minPosition.x);
			minPosition.y = min(v.y, minPosition.y);

			maxPosition.x = max(v.x, maxPosition.x);
			maxPosition.y = max(v.y, maxPosition.y);

			m_Vertices.push_back({ v, false });
		}

		{
			vec2f delta = maxPosition - minPosition;
			m_BoundingBox = rect2f(minPosition.x, minPosition.y, delta.x, delta.y);
		}

		//Hacky fix for edge cases
		//Doesn't always work, need to find a way to get this to always work
		float m = (maxPosition - minPosition).magnitude();
		minPosition -= 10 * m;
		maxPosition += 10 * m;

		vec2f delta = maxPosition - minPosition;

		m_Vertices.push_back({ minPosition, false });
		m_Vertices.push_back({ minPosition + vec2f(delta.x * 2, 0) });
		m_Vertices.push_back({ minPosition + vec2f(0, delta.y * 2) });

		TriangleRef superTriangle = { (int)m_Vertices.size() - 1, (int)m_Vertices.size() - 2, (int)m_Vertices.size() - 3 };

		//bowyer watson super triangle
		m_Triangles.push_back(superTriangle);

		for (int i = 0; i < m_Vertices.size() - 3; i++) { //Ignore the last few vertices
			const vec2f &v = m_Vertices[i].m_Vertex;

			std::vector<TriangleRef> badTriangles;

			//Resulting polygon
			std::map<EdgeRef, int> polygon;

			//Find all bad triangles
			for (auto &t : m_Triangles) {
				triangle2f tr = triangle2f(
					m_Vertices[t.a].m_Vertex,
					m_Vertices[t.b].m_Vertex,
					m_Vertices[t.c].m_Vertex
				);
				if (contains(tr.circumcircle(), v)) {
					badTriangles.push_back(t);

					//If the int is > 1, its a shared edge
					polygon[{ t.a, t.b }]++;
					polygon[{ t.b, t.c }]++;
					polygon[{ t.c, t.a }]++;
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
			if(superTriangle.contains(t.a) || superTriangle.contains(t.b) || superTriangle.contains(t.c)){
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
	triangle2f Delaunay::getTriangle(int index) const
	{
		TriangleRef ref = getTriangleRef(index);

		return triangle2f(
			getPoint(ref.a),
			getPoint(ref.b),
			getPoint(ref.c));
	}

	bool TriangleRef::operator==(const TriangleRef & other) const
	{
		//TODO order
		return a == other.a && b == other.b && c == other.c;
	}

	bool TriangleRef::contains(int i)
	{
		return a == i || b == i || c == i;
	}
	EdgeRef::EdgeRef(int a, int b)
		: a(min(a,b)), b(max(a,b)) //Sort this shit
	{ }

	bool EdgeRef::contains(int i)
	{
		return a == i || b == i;
	}

	bool EdgeRef::operator==(const EdgeRef & other) const
	{
		if (a == other.a && b == other.b)
			return true;
		if (a == other.b && b == other.a)
			return true;
		return false;
	}
	bool EdgeRef::operator<(const EdgeRef & other) const
	{
		if (a < other.a)
			return true;
		if (a == other.a)
			return b < other.b;
		return false;
	}
}
