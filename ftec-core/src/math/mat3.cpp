#include "mat3.h"
#include "mat4.h"

#include "vec2.h"
#include "vec3.h"

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
		multiply(mat3<T>({
			1,0,x,
			0,1,y,
			0,0,1,
		}));
		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::scale(T x, T y)
	{
		multiply(mat3<T>({
			x,0,0,
			0,y,0,
			0,0,1,
		}));
		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::rotate(T angle)
	{
		T r = angle * ((T)3.141592654 / (T)180.0);
		T s = sin(r);
		T c = cos(r);

		multiply(mat3<T>({
			c,-s,0,
			s,c,0,
			0,0,1,
		}));

		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::multiply(const mat3<T>& other)
	{
		T sum;
		mat3<T> m;

		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				sum = 0;
				for (int e = 0; e < 3; ++e) {
					sum += elements[e + y * 3] * other.elements[x + e * 3];
				}

				m.elements[x + y * 3] = sum;
			}
		}

		elements = m.elements;

		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::transpose()
	{
		//Copy this
		mat3<T> m = *this;

		for (int collumn = 0; collumn < 3; collumn++) {
			for (int row = 0; row < 3; row++) {
				//Swap swapperdie swapswap
				el(row, collumn) = m.el(collumn, row);
			}
		}

		return *this;
	}

	template<typename T>
	mat3<T>& mat3<T>::inverse()
	{
		return *this;
	}

	template<typename T>
	mat3<T> mat3<T>::multiplied(const mat3<T>& m) const
	{
		return clone().multiply(m);
	}

	template<typename T>
	mat3<T> mat3<T>::transposed() const
	{
		return clone().transpose();
	}

	template<typename T>
	mat4<T> mat3<T>::expand() const
	{
		//[ a b c ]
		//[ d e f ]
		//[ g h i ]

		//[ a b 0 c ]
		//[ d e 0 f ]
		//[ 0 0 1 0 ]
		//[ 0 0 0 1 ]

		return mat4<T>(
		{
			a,b,0,c,
			d,e,0,f,
			0,0,1,0,
			0,0,0,1
		});
	}

	template<typename T>
	mat3<T> mat3<T>::inversed() const
	{
		return clone().inverse();
	}

	template<typename T>
	mat3<T> mat3<T>::clone() const
	{
		return mat3<T>(*this);
	}

	template <typename T>
	T mat3<T>::determinant() const
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

	template <typename T>
	mat3<T> &mat3<T>::operator *=(const mat3<T> other)
	{
		return multiply(other);
	}

	template <typename T>
	mat3<T> mat3<T>::operator*(const mat3<T> &right) const
	{
		return multiplied(right);
	}
	template <typename T>
	vec2<T> mat3<T>::operator*(const vec2<T> &right) const
	{
		return vec2<T>(
			el(0, 0) * right.x + el(1, 0) * right.y + el(2, 0),
			el(0, 1) * right.x + el(1, 1) * right.y + el(2, 1)
			);
	}
	template <typename T>
	vec3<T> mat3<T>::operator*(const vec3<T> &right) const
	{
		return vec3<T>(
			el(0, 0) * right.x + el(1, 0) * right.y + el(2, 0) * right.z,
			el(0, 1) * right.x + el(1, 1) * right.y + el(2, 1) * right.z,
			el(0, 2) * right.x + el(1, 2) * right.y + el(2, 2) * right.z
			);
	}

	//Tyvm compiler for compiling this
	template struct mat3<float>;
	template struct mat3<double>;
}
