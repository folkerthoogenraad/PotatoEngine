#include "Matrix2.h"

namespace ftec {

	template <typename T>
	Matrix2<T>::Matrix2()
	{
		std::fill(elements.begin(), elements.end(), (T)0);
		elements[0 + 0 * 1] = (T)1;
		elements[1 + 1 * 1] = (T)1;
	}
	
	template<typename T>
	Matrix2<T>& Matrix2<T>::multiply(const Matrix2<T>& other)
	{
		T sum;
		Matrix2<T> m;

		for (int y = 0; y < 2; ++y) {
			for (int x = 0; x < 2; ++x) {
				sum = 0;
				for (int e = 0; e < 2; ++e) {
					sum += elements[e + y * 2] * other.elements[x + e * 2];
				}

				m.elements[x + y * 2] = sum;
			}
		}

		elements = m.elements;

		return *this;
	}

	template<typename T>
	Matrix2<T> Matrix2<T>::multiplied(const Matrix2<T>& m) const
	{
		return clone().multiply(m);
	}

	template<typename T>
	Matrix2<T>& Matrix2<T>::transpose()
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = i + i; j < 2; j++)
			{
				std::swap(el(i, j), el(j, i));
			}
		}

		return *this;
	}

	template<typename T>
	Matrix2<T> Matrix2<T>::transposed() const
	{
		return clone().transpose();
	}

	template<typename T>
	Matrix2<T>& Matrix2<T>::inverse()
	{
		return *this;
	}

	template<typename T>
	Matrix2<T> Matrix2<T>::inversed() const
	{
		return clone().inverse();
	}

	template<typename T>
	inline Matrix2<T> Matrix2<T>::clone() const
	{
		
		return Matrix2<T>(*this);
	}

	template<typename T>
	T Matrix2<T>::determinant() const
	{
		return a * d - b * c;
	}

	template<typename T>
	Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T> other)
	{
		return multiply(other);
	}

	template<typename T>
	Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& right) const
	{
		return multiplied(right);
	}

	template struct Matrix2<float>;
	template struct Matrix2<double>;
	template struct Matrix2<int>;
	template struct Matrix2<long long>;
}