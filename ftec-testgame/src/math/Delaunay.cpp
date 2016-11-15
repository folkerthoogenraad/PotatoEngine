#include "Delaunay.h"

#include <algorithm>
#include <set>

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

		m_Vertices = points;

		sort(m_Vertices.begin(), m_Vertices.end(), 
			[](const vec2f &a, const vec2f &b) -> bool {
			if (a.x > b.x)
				return true;
			if (a.x == b.x)
				return a.y > b.y;
			else
				return false;
		});

		vec2f minPosition = m_Vertices.front();
		vec2f maxPosition = minPosition;

		for (auto & v : m_Vertices) {
			minPosition.x = min(v.x, minPosition.x);
			minPosition.y = min(v.y, minPosition.y);

			maxPosition.x = max(v.x, maxPosition.x);
			maxPosition.y = max(v.y, maxPosition.y);
		}

		float m = (maxPosition - minPosition).magnitude();
		minPosition -= m;
		maxPosition += m;

		vec2f delta = maxPosition - minPosition;


		m_Vertices.push_back(minPosition);
		m_Vertices.push_back(minPosition + vec2f(delta.x * 2, 0));
		m_Vertices.push_back(minPosition + vec2f(0, delta.y * 2));

		TriangleRef superTriangle = { (int)m_Vertices.size() - 1, (int)m_Vertices.size() - 2, (int)m_Vertices.size() - 3 };

		//bowyer watson super triangle
		m_Triangles.push_back(superTriangle);

		for (int i = 0; i < m_Vertices.size() - 3; i++) { //Ignore the last few vertices
			const vec2f &v = m_Vertices[i];

			std::vector<TriangleRef> badTriangles;

			//Resulting polygon
			std::vector<EdgeRef> polygon;

			//Find all bad triangles
			for (auto &t : m_Triangles) {
				triangle2f tr = triangle2f(
					m_Vertices[t.a],
					m_Vertices[t.b],
					m_Vertices[t.c]
				);
				if(contains(tr.circumcircle(), v)){
					badTriangles.push_back(t);

					polygon.push_back({ t.a, t.b });
					polygon.push_back({ t.b, t.c });
					polygon.push_back({ t.c, t.a });
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


			//Shared edges
			std::vector<EdgeRef> badEdges;
			for (auto i = polygon.begin(); i != polygon.end(); ++i) {
				for (auto j = polygon.begin(); j != polygon.end(); ++j) {
					if (i == j) continue;
					if (*i == *j) {
						badEdges.push_back(*i);
						badEdges.push_back(*j);
					}
				}
			}

			//Remove the badEdges
			polygon.erase(std::remove_if(polygon.begin(), polygon.end(),
				[&badEdges](EdgeRef &t) {
				for (auto &tr : badEdges) {
					if (tr == t)
						return true;
				}
				return false;
			}), polygon.end());

			for (auto &e : polygon) {
				m_Triangles.push_back({
					e.a, e.b, i
				});
			}
		}

		m_Triangles.erase(std::remove_if(m_Triangles.begin(), m_Triangles.end(),
			[&superTriangle](TriangleRef &t) {
			return superTriangle.contains(t.a) || superTriangle.contains(t.b) || superTriangle.contains(t.c);
		}), m_Triangles.end());

		for (int i = 0; i < 3; i++)
			m_Vertices.pop_back();

	}
	triangle2f Delaunay::getTriangle(int index)
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
