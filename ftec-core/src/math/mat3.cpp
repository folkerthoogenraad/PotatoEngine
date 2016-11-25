#include "mat3.h"



namespace ftec {

	template <typename T>
	mat3<T>::mat3()
	{
		std::fill(elements.begin(), elements.end(), (T)0);
		elements[0 + 0 * 3] = (T)1;
		elements[1 + 1 * 3] = (T)1;
		elements[2 + 2 * 3] = (T)1;
	}

	template <typename T>
	T mat3<T>::determinant()
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

	//Tyvm compiler for compiling this
	template struct mat3<float>;
	template struct mat3<int>;
	template struct mat3<double>;
}
