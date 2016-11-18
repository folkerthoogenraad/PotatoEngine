#pragma once

#include "math/vec3.h"
#include "math/box.h"
#include <vector>

namespace ftec {
	class Delaunay3D {
	public:

		struct TetrahedronRef {
			int a, b, c, d;

			bool contains(int i);
			bool operator==(const TetrahedronRef &other);
		};

		struct TriangleRef {
			int a, b, c;

			TriangleRef(int a, int b, int c);

			bool contains(int i);
			bool operator==(const TriangleRef &other) const;
			bool operator<(const TriangleRef &other) const;
		};

	private:
		std::vector<vec3f> m_Vertices;

		std::vector<TetrahedronRef> m_Tetrahedrons;

		boxf m_BoundingBox;
	public:
		Delaunay3D() {}
		Delaunay3D(std::vector<vec3f> points);

		void triangulate(std::vector<vec3f> points);

		int getPointCount() const { return m_Vertices.size(); };
		const vec3f &getPoint(int index) const { return m_Vertices[index]; }

		int getTetraHedronCount() const { return m_Tetrahedrons.size(); }
		const TetrahedronRef &getTetraHedronRef(int index) const { return m_Tetrahedrons[index]; }

		const boxf &getBoundingBox() const { return m_BoundingBox; }
	};
}