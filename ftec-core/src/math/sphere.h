#pragma once

#include "Vector3.h"

namespace ftec {

	template<typename T>
	struct sphere {
		Vector3<T> center;
		T radius;

		sphere() {}
		sphere(const Vector3<T> &c, T radius)
			: center(c), radius(radius) {}

		sphere<T> &transform(const Matrix4<T> m)
		{
			//TODO PLS PLS

			return *this;
		}
		sphere<T> transformed() const
		{
			return clone().transform(m);
		}

		sphere<T> &flip()
		{
			radius = -radius;
			return *this;
		}
		sphere<T> flipped() const
		{
			return clone().flip();
		}

		sphere<T> &orient()
		{
			radius = abs(radius);
			return *this;
		}
		sphere<T> oriented() const
		{
			return clone().orient();
		}

		T magnitude() const { return radius; }
		sphere<T> clone() const { return sphere<T>(*this); }
	};

	typedef sphere<float> spheref;
	typedef sphere<double> sphered;
	typedef sphere<int> spherei;
}