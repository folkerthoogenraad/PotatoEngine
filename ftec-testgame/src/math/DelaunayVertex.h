#pragma once

namespace ftec {
	
	template <typename T>
	struct DelaunayVertex {
		T m_Vertex;
		bool m_Hull;
		bool m_Super;
	};

	struct TetrahedronRef {
		int a, b, c, d;

		TetrahedronRef(int a, int b, int c, int d);

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

	struct EdgeRef {
		int a, b;

	public:
		EdgeRef(int a, int b);

		bool contains(int i);
		bool operator==(const EdgeRef &other) const;
		bool operator<(const EdgeRef &other) const;
	};

}