#pragma once

#include <iostream>
#include <array>

//The matrix class, layed out in memory as:
//[ a b c ]
//[ d e f ]
//[ g h i ]

namespace ftec {

	template<typename T>
	struct vec2;
	template<typename T>
	struct vec3;

	template<typename T>
	struct mat4;

	template<typename T>
	struct mat3
	{
		union {
			std::array<T, 3 * 3> elements;

			struct {
				T a, b, c, d, e, f, g, h, i;
			};
		};

		mat3();
		mat3(std::array<T, 3 * 3> elements) : elements(elements) {}

		mat3<T> &translate(T x, T y);
		mat3<T> &scale(T x, T y);
		mat3<T> &rotate(T x);

		mat3<T> &multiply(const mat3<T> &m);
		mat3<T> multiplied(const mat3<T> &m) const;

		mat3<T> &transpose();
		mat3<T> transposed() const;

		mat3<T> &inverse();
		mat3<T> inversed() const;

		mat3<T> clone() const;

		mat4<T> expand() const;

		T determinant() const;

		mat3<T> &operator *=(const mat3<T> other);

		mat3<T> operator*(const mat3<T> &right) const;
		vec2<T> operator*(const vec2<T> &right) const;
		vec3<T> operator*(const vec3<T> &right) const;

		inline T &el(int column, int row) { return elements[column + row * 3]; }
		inline T el(int column, int row) const { return elements[column + row * 3]; }
	};




	typedef mat3<float> mat3f;
	typedef mat3<double> mat3d;
	typedef mat3<int> mat3i;
}