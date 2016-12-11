#pragma once

#include "Vector3.h"

namespace ftec {

	template<typename T>
	struct Sphere;
	template<typename T>
	struct Matrix4;

	template<typename T>
	struct Cuboid {
		Vector3<T> min;
		Vector3<T> max;

		Cuboid() {}
		Cuboid(Vector3<T> mn, Vector3<T> mx) : min(mn), max(mx) {}

		Vector3<T> center() const { return (min + max) / 2; }
		Vector3<T> extends() const { return max - center(); }

		T magnitude() const { return extends().magnitude(); }

		Cuboid<T> &transform(const Matrix4<T> &m)
		{
			min = m * min;
			max = m * max;
			return *this;
		}
		Cuboid<T> transformed(const Matrix4<T> &m) const
		{
			return clone().transform(m);
		}

		Cuboid<T> &flip()
		{
			Vector3<T> t = max;
			max = min;
			min = t;

			return *this;
		}
		Cuboid<T> flipped() const
		{
			return clone().flip();
		}

		Cuboid<T> clone() const { return Cuboid<T>(*this); }
		Sphere<T> boudingsphere() const {
			return Sphere<T>(
				(min + max) / 2,
				(max - min).magnitude() / 2
				);
		}
	};

	typedef Cuboid<float> Cuboidf;
	typedef Cuboid<double> Cuboidd;
	typedef Cuboid<int> Cuboidi;
}