#pragma once

#include "math/vec3.h"
#include "math/box.h"
#include <vector>
#include "DelaunayVertex.h"

namespace ftec {
	class Delaunay3D {
	private:
		std::vector<DelaunayVertex<vec3f>> m_Vertices;
		std::vector<TetrahedronRef> m_Tetrahedrons;
		std::vector<TriangleRef> m_HullTriangles;

		boxf m_BoundingBox;
	public:
		Delaunay3D() {}
		Delaunay3D(std::vector<vec3f> points);

		void triangulate(std::vector<vec3f> points);

		int getPointCount() const { return m_Vertices.size(); };
		const vec3f &getPoint(int index) const { return m_Vertices[index].m_Vertex; }
		bool isHull(int index) const { return m_Vertices[index].m_Hull; }

		int getTetraHedronCount() const { return (int) m_Tetrahedrons.size(); }
		const TetrahedronRef &getTetraHedronRef(int index) const { return m_Tetrahedrons[index]; }

		int getHullTriangleCount() const { return (int) m_HullTriangles.size(); }
		const TriangleRef &getHullTriangleRef(int index) const { return m_HullTriangles[index]; }

		const boxf &getBoundingBox() const { return m_BoundingBox; }
	};
}