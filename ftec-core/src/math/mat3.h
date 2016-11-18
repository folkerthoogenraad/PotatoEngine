#pragma once
#include <iostream>
#include <array>

namespace ftec {

	struct mat3
	{
		union {
			std::array<float, 3 * 3> elements;

			struct {
				float a, b, c, d, e, f, g, h, i;
			};
		};

		//[ 1 2 3 ]
		//[ 4 5 6 ]
		//[ 7 8 9 ]

		mat3();
		mat3(std::array<float, 3 * 3> elements) : elements(elements) {}

		float determinant();

		inline float &el(int column, int row) { return elements[column + row * 3]; }
		inline float el(int column, int row) const { return elements[column + row * 3]; }

		friend std::ostream& operator<<(std::ostream& left, const mat3& right);
	};
}