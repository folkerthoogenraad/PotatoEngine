#pragma once

#include <iostream>
#include <array>

namespace ftec {

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

		T determinant();

		inline T &el(int column, int row) { return elements[column + row * 3]; }
		inline T el(int column, int row) const { return elements[column + row * 3]; }

		friend std::ostream& operator<<(std::ostream& left, const mat3& right);
	};
}