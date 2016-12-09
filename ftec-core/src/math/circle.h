#pragma once

#include "Vector2.h"

namespace ftec {

	template<typename T>
	struct Matrix3;

	template<typename T>
	struct circle {
		Vector2<T> center;
		T radius;

		circle() {}
		circle(const Vector2<T> &c, T radius)
			: center(c), radius(radius) {}

		circle<T> &transform(const Matrix3<T> m)
		{
			//TODO PLS PLS

			return *this;
		}
		circle<T> transformed() const 
		{
			return clone().transform(m);
		}

		circle<T> &flip()
		{
			radius = -radius;
			return *this;
		}
		circle<T> flipped() const
		{
			return clone().flip();
		}

		circle<T> &orient()
		{
			radius = abs(radius);
			return *this;
		}
		circle<T> oriented() const
		{
			return clone().orient();
		}

		T magnitude() const { return radius; }
		circle<T> clone() const { return circle<T>(*this); }
	};

	typedef circle<float> circlef;
	typedef circle<double> circled;
	typedef circle<int> circlei;
}