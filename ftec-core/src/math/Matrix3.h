#pragma once

#include <iostream>
#include <array>

//The matrix class, layed out in memory as:
//[ a b c ]
//[ d e f ]
//[ g h i ]

namespace ftec {

	template<typename T>
	struct Vector2;
	template<typename T>
	struct Vector3;

	template<typename T>
	struct Matrix4;

	template<typename T>
	struct Matrix3
	{
		union {
			std::array<T, 3 * 3> elements;

			struct {
				T a, b, c, d, e, f, g, h, i;
			};
		};

		Matrix3();
		Matrix3(std::array<T, 3 * 3> elements) : elements(elements) {}

		Matrix3<T> &translate(T x, T y);
		Matrix3<T> &scale(T x, T y);
		Matrix3<T> &rotate(T x);

		Matrix3<T> &multiply(const Matrix3<T> &m);
		Matrix3<T> multiplied(const Matrix3<T> &m) const;

		Matrix3<T> &transpose();
		Matrix3<T> transposed() const;

		Matrix3<T> &inverse();
		Matrix3<T> inversed() const;

		Matrix3<T> clone() const;

		Matrix4<T> expand() const;

		T determinant() const;

		Matrix3<T> &operator *=(const Matrix3<T> other);

		Matrix3<T> operator*(const Matrix3<T> &right) const;
		Vector2<T> operator*(const Vector2<T> &right) const;
		Vector3<T> operator*(const Vector3<T> &right) const;

		inline T &el(int column, int row) { return elements[column + row * 3]; }
		inline T el(int column, int row) const { return elements[column + row * 3]; }
	};




	typedef Matrix3<float> Matrix3f;
	typedef Matrix3<double> Matrix3d;
}