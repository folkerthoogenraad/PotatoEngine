#pragma once

#include <vector>
#include "math/math.h"
#include "math/triangle.h"

namespace ftec {

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

	class Delaunay {
		std::vector<vec2f> m_Vertices;

		std::vector<TriangleRef> m_Triangles;
	public:
		Delaunay() {}
		Delaunay(std::vector<vec2f> points);

		void triangulate(std::vector<vec2f> points);

		int getPointCount() { return m_Vertices.size(); };
		const vec2f &getPoint(int index) { return m_Vertices[index]; }

		int getTriangleCount() { return m_Triangles.size(); }
		TriangleRef getTriangleRef(int index) { return m_Triangles[index]; }
		triangle2f getTriangle(int index);

	};
}