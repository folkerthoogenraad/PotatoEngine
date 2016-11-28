#pragma once

#include <iostream>
#include <array>

namespace ftec {

	template<typename T>
	struct vec2;

	template<typename T>
	struct mat3
	{
		union {
			std::array<T, 3 * 3> elements;

			struct {
				T a, b, c, d, e, f, g, h, i;
			};
		};

		//[ 1 2 3 ]
		//[ 4 5 6 ]
		//[ 7 8 9 ]

		mat3();
		mat3(std::array<T, 3 * 3> elements) : elements(elements) {}

		mat3<T> &translate(T x, T y);
		mat3<T> &scale(T x, T y);
		mat3<T> &rotate(T x);

		mat3<T> &multiply(const mat3<T> &m);
		mat3<T> multiplied(const mat3<T> &m);

		mat3<T> &transpose();
		mat3<T> transposed();

		mat3<T> &inverse();
		mat3<T> inversed();

		mat3<T> clone();

		T determinant();

		inline T &el(int column, int row) { return elements[column + row * 3]; }
		inline T el(int column, int row) const { return elements[column + row * 3]; }
	};

	typedef mat3<float> mat3f;
	typedef mat3<double> mat3d;
	typedef mat3<int> mat3i;

	typedef mat3<long> mat3l;
	typedef mat3<long long> mat3ll;
}