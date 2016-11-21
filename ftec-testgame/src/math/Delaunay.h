#pragma once

#include <vector>
#include "math/triangle2.h"
#include "math/rect.h"

#include "DelaunayVertex.h"

namespace ftec {

	class Delaunay {
	private:
		std::vector<DelaunayVertex<vec2f>> m_Vertices;

		std::vector<TriangleRef> m_Triangles;

		rectf m_BoundingBox;
	public:
		Delaunay() {}
		Delaunay(std::vector<vec2f> points);

		void triangulate(std::vector<vec2f> points);

		int getPointCount() const { return m_Vertices.size(); };
		const vec2f &getPoint(int index) const { return m_Vertices[index].m_Vertex; }
		const std::vector<DelaunayVertex<vec2f>> &getVertices() const { return m_Vertices; }

		int getTriangleCount() const { return m_Triangles.size(); }
		const TriangleRef &getTriangleRef(int index) const { return m_Triangles[index]; }
		triangle2f getTriangle(int index) const;

		const rectf &getBoundingBox() const { return m_BoundingBox; }
	};
}