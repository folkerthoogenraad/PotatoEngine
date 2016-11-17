#pragma once

#include <vector>
#include "math/triangle2.h"
#include "math/rect.h"

namespace ftec {

	//Imo, this is very stupid and it looks dull
	struct ConvexVertex {
		vec2f m_Vertex;
		bool m_Hull;
	};

	class Delaunay {
	public:
		struct TriangleRef {
			int a, b, c;

			bool contains(int i);
			bool operator==(const TriangleRef &other) const;
		};
		struct EdgeRef {
			int a, b;

		public:
			EdgeRef(int a, int b);

			bool contains(int i);
			bool operator==(const EdgeRef &other) const;
			bool operator<(const EdgeRef &other) const;
		};

	private:
		std::vector<ConvexVertex> m_Vertices;

		std::vector<TriangleRef> m_Triangles;

		rect2f m_BoundingBox;
	public:
		Delaunay() {}
		Delaunay(std::vector<vec2f> points);

		void triangulate(std::vector<vec2f> points);

		int getPointCount() const { return m_Vertices.size(); };
		const vec2f &getPoint(int index) const { return m_Vertices[index].m_Vertex; }
		const std::vector<ConvexVertex> &getVertices() const { return m_Vertices; }

		int getTriangleCount() const { return m_Triangles.size(); }
		const TriangleRef &getTriangleRef(int index) const { return m_Triangles[index]; }
		triangle2f getTriangle(int index) const;

		const rect2f &getBoundingBox() const { return m_BoundingBox; }
	};
}