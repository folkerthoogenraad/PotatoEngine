#pragma once

#include "Vector3.h"

namespace ftec {

	template <typename T>
	struct line3;

	template<typename T>
	struct triangle3 {
		Vector3<T> a;
		Vector3<T> b;
		Vector3<T> c;

		triangle3() {}
		triangle3(const Vector3<T> &a, const Vector3<T> &b, const Vector3<T> &c)
			: a(a), b(b), c(c) {}

		triangle3<T> &translate(Vector3<T> v)
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

		triangle3<T> &flip() {
			std::swap(a, b);
			return *this;
		}

		line3<T> edgeab() const { return line3<T>(a, b); }
		line3<T> edgebc() const { return line3<T>(b, c); }
		line3<T> edgeca() const { return line3<T>(c, a); }

		template <typename T>
		static triangle3<T> unitTriangle()
		{
			return triangle3<T>(
				Vector3<T>(-0.5f, 0, -1.f / 3.f*sqrt(0.75)),
				Vector3<T>(0.5f, 0, -1.f / 3.f*sqrt(0.75)),
				Vector3<T>(0, 0, 2.f/3.f*sqrt(0.75))
				);
		}
	};

	typedef triangle3<float> triangle3f;
	typedef triangle3<double> triangle3d;
	typedef triangle3<int> triangle3i;

}