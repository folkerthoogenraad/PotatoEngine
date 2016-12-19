#pragma once

#include <array>

namespace ftec {
	template<typename T>
	struct Matrix2
	{
		union {
			std::array<T, 2 * 2> elements;

			struct {
				T a, b, c, d;
			};
		};

		Matrix2();
		Matrix2(std::array<T, 2 * 2> elements) : elements(elements) {}

		Matrix2<T> &multiply(const Matrix2<T> &m);
		Matrix2<T> multiplied(const Matrix2<T> &m) const;

		Matrix2<T> &transpose();
		Matrix2<T> transposed() const;

		Matrix2<T> &inverse();
		Matrix2<T> inversed() const;

		Matrix2<T> clone() const;

		T determinant() const;

		Matrix2<T> &operator *=(const Matrix2<T> other);
		Matrix2<T> operator*(const Matrix2<T> &right) const;

		inline T &el(int column, int row) { return elements[column + row * 3]; }
		inline T el(int column, int row) const { return elements[column + row * 3]; }
	};

	typedef Matrix2<float> Matrix2f;
	typedef Matrix2<double> Matrix2d;
	typedef Matrix2<int> Matrix2i;
	typedef Matrix2<long long> Matrix2ll;
}