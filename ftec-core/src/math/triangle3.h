#pragma once

#include "Vector3.h"

namespace ftec {

	template <typename T>
	struct Line3;

	template<typename T>
	struct Triangle3 {
		Vector3<T> a;
		Vector3<T> b;
		Vector3<T> c;

		Triangle3() {}
		Triangle3(const Vector3<T> &a, const Vector3<T> &b, const Vector3<T> &c)
			: a(a), b(b), c(c) {}

		Triangle3<T> &translate(Vector3<T> v)
		{
			a += v;
			b += v;
			c += v;

			return *this;
		}

		//The normal is NOT normalized
		Vector3<T> normal() const
		{
			return Vector3<T>::cross(b - a, c - a);
		}

		//The distance is in abstract triangle units
		T distanceFrom(Vector3<T> point)
		{
			return Vector3<T>::dot(normal(), point - a);
		}

		Triangle3<T> &flip() {
			std::swap(a, b);
			return *this;
		}

		Line3<T> edgeab() const { return Line3<T>(a, b); }
		Line3<T> edgebc() const { return Line3<T>(b, c); }
		Line3<T> edgeca() const { return Line3<T>(c, a); }

		template <typename T>
		static Triangle3<T> unitTriangle()
		{
			return Triangle3<T>(
				Vector3<T>(-0.5f, 0, -1.f / 3.f*sqrt(0.75)),
				Vector3<T>(0.5f, 0, -1.f / 3.f*sqrt(0.75)),
				Vector3<T>(0, 0, 2.f/3.f*sqrt(0.75))
				);
		}
	};

	typedef Triangle3<float> Triangle3f;
	typedef Triangle3<double> Triangle3d;
	typedef Triangle3<int> Triangle3i;

}