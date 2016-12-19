#pragma once

#include "Vector2.h"

namespace ftec {

	template<typename T>
	struct Matrix3;

	template<typename T>
	struct Circle {
		Vector2<T> center;
		T radius;

		Circle() {}
		Circle(const Vector2<T> &c, T radius)
			: center(c), radius(radius) {}

		Circle<T> &transform(const Matrix3<T> m)
		{
			//TODO PLS PLS

			return *this;
		}
		Circle<T> transformed() const 
		{
			return clone().transform(m);
		}

		Circle<T> &flip()
		{
			radius = -radius;
			return *this;
		}
		Circle<T> flipped() const
		{
			return clone().flip();
		}

		Circle<T> &orient()
		{
			radius = abs(radius);
			return *this;
		}
		Circle<T> oriented() const
		{
			return clone().orient();
		}

		T magnitude() const { return radius; }
		Circle<T> clone() const { return Circle<T>(*this); }
	};

	typedef Circle<float> Circlef;
	typedef Circle<double> Circled;
	typedef Circle<int> Circlei;
	typedef Circle<long long> Circlell;
}