#include "DelaunayVertex.h"

#include <array>
#include "math/math.h"

namespace ftec {

	EdgeRef::EdgeRef(int a, int b)
		: a(min(a, b)), b(max(a, b)) //Sort this shit
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

	TriangleRef::TriangleRef(int a, int b, int c)
	{
		//DIRTY DIRTY DIRTY
		std::array<int, 3> s{ a, b, c };
		std::sort(s.begin(), s.end());
		this->a = s[0];
		this->b = s[1];
		this->c = s[2];
	}

	bool TriangleRef::contains(int i)
	{
		return a == i || b == i || c == i;
	}

	bool TriangleRef::operator==(const TriangleRef & other) const
	{
		return a == other.a && b == other.b && c == other.c;
	}

	bool TriangleRef::operator<(const TriangleRef & other) const
	{
		if (a < other.a)
			return true;
		if (a == other.a) {
			if (b < other.b)
				return true;
			if (b == other.b)
				return c < other.c;
		}

		return false;
	}

	TetrahedronRef::TetrahedronRef(int a, int b, int c, int d)
	{
		//DIRTY DIRTY DIRTY
		std::array<int, 4> s{ a, b, c, d };
		std::sort(s.begin(), s.end());
		this->a = s[0];
		this->b = s[1];
		this->c = s[2];
		this->d = s[3];
	}

	bool TetrahedronRef::contains(int i)
	{
		return a == i || b == i || c == i || d == i;
	}

	bool TetrahedronRef::operator==(const TetrahedronRef & other)
	{
		return a == other.a && b == other.b && c == other.c && d == other.d;
	}
}
