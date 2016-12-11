#pragma once

#include "Vector3.h"

namespace ftec {

	template<typename T>
	struct Sphere {
		Vector3<T> center;
		T radius;

		Sphere() {}
		Sphere(const Vector3<T> &c, T radius)
			: center(c), radius(radius) {}

		Sphere<T> &transform(const Matrix4<T> m)
		{
			//TODO PLS PLS

			return *this;
		}
		Sphere<T> transformed() const
		{
			return clone().transform(m);
		}

		Sphere<T> &flip()
		{
			radius = -radius;
			return *this;
		}
		Sphere<T> flipped() const
		{
			return clone().flip();
		}

		Sphere<T> &orient()
		{
			radius = abs(radius);
			return *this;
		}
		Sphere<T> oriented() const
		{
			return clone().orient();
		}

		T magnitude() const { return radius; }
		Sphere<T> clone() const { return Sphere<T>(*this); }
	};

	typedef Sphere<float> Spheref;
	typedef Sphere<double> Sphered;
	typedef Sphere<int> Spherei;
}