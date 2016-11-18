#include "mat3.h"



namespace ftec {
	mat3::mat3()
	{
		std::fill(elements.begin(), elements.end(), 0);
		elements[0 + 0 * 3] = 1;
		elements[1 + 1 * 3] = 1;
		elements[2 + 2 * 3] = 1;
	}

	float mat3::determinant()
	{
		//[a b c]
		//[d e f]
		//[g h i]

		return
			a * e * i +	//aei
			b * f * g +	//bfg
			c * d * h -	//cdh

			c * e * g -	//ceg
			b * d * i -	//bdi
			a * f * h;	//afh
	}

	std::ostream & ftec::operator<<(std::ostream & left, const mat3 & right)
	{
		for (int row = 0; row < 3; ++row) {
			left << "[";
			for (int column = 0; column < 3; ++column) {
				left << right.el(column, row);// [column + row * 3];
				if (column != 2)
					left << ", ";
			}
			left << "]" << std::endl;
		}

		return left;
	}
}
