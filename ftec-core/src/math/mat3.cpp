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

	template<typename T>
	mat3<T>& mat3<T>::translate(T x, T y)
	{
		for (int row = 0; row < 3; row++) {
			int i = row * 3;
			elements[i + 2] = elements[i] * x + elements[i + 1] * y + elements[i + 2];
		}
		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::scale(T x, T y)
	{
		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::rotate(T x)
	{
		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::multiply(const mat3<T>& m)
	{
		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::transpose()
	{
		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::inverse()
	{
		return *this;
	}

	template<typename T>
	mat3<T> mat3<T>::multiplied()
	{
		return mat3<T>();
	}

	template<typename T>
	mat3<T> mat3<T>::transposed()
	{
		return mat3<T>();
	}

	template<typename T>
	mat3<T> mat3<T>::inversed()
	{
		return mat3<T>();
	}

	template<typename T>
	mat3<T> mat3<T>::clone()
	{
		return mat3<T>(*this);
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
