#include "Matrix3.h"
#include "Matrix4.h"

#include "Vector2.h"
#include "Vector3.h"

namespace ftec {

	template <typename T>
	Matrix3<T>::Matrix3()
	{
		std::fill(elements.begin(), elements.end(), (T)0);
		elements[0 + 0 * 3] = (T)1;
		elements[1 + 1 * 3] = (T)1;
		elements[2 + 2 * 3] = (T)1;
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::translate(T x, T y)
	{
		multiply(Matrix3<T>({
			1,0,x,
			0,1,y,
			0,0,1,
		}));
		return *this;
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::identity()
	{
		return Matrix3<T>();
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::translation(T x, T y)
	{
		return Matrix3<T>().translate(x, y);
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::translation(Vector2<T> v)
	{
		return translation(v.x, v.y);
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::scaled(T x, T y)
	{
		return Matrix3<T>().scale(x,y);
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::scaled(Vector2<T> v)
	{
		return scaled(v.x, v.y);
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::scale(T x, T y)
	{
		multiply(Matrix3<T>({
			x,0,0,
			0,y,0,
			0,0,1,
		}));
		return *this;
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::rotation(T x)
	{
		return Matrix3<T>().rotate(x);
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::rotate(T angle)
	{
		T r = angle * ((T)3.141592654 / (T)180.0);
		T s = (T) sin(r);
		T c = (T) cos(r);

		multiply(Matrix3<T>({
			c,-s,0,
			s,c,0,
			0,0,1,
		}));

		return *this;
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::multiply(const Matrix3<T>& other)
	{
		T sum;
		Matrix3<T> m;

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
	Matrix3<T>& Matrix3<T>::multiply(const T & t)
	{
		for (int i = 0; i < elements.size(); i++) {
			elements[i] *= t;
		}
		return *this;
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::multiplied(const T & t) const
	{
		return clone().multiply(t);
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::transpose()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = i + i; j < 3; j++)
			{
				std::swap(el(i, j), el(j, i));
			}
		}

		return *this;
	}

	template<typename T>
	Matrix3<T>& Matrix3<T>::inverse()
	{
		T d = determinant();

		return multiply((T)1.0 / d);
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::multiplied(const Matrix3<T>& m) const
	{
		return clone().multiply(m);
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::transposed() const
	{
		return clone().transpose();
	}

	template<typename T>
	Matrix4<T> Matrix3<T>::expand() const
	{
		//[ a b c ]
		//[ d e f ]
		//[ g h i ]

		//[ a b 0 c ]
		//[ d e 0 f ]
		//[ 0 0 1 0 ]
		//[ 0 0 0 1 ]

		return Matrix4<T>(
		{
			a,b,0,c,
			d,e,0,f,
			0,0,1,0,
			0,0,0,1
		});
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::inversed() const
	{
		return clone().inverse();
	}

	template<typename T>
	Matrix3<T> Matrix3<T>::clone() const
	{
		return Matrix3<T>(*this);
	}

	template <typename T>
	T Matrix3<T>::determinant() const
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
	Matrix3<T> &Matrix3<T>::operator *=(const Matrix3<T> other)
	{
		return multiply(other);
	}

	template <typename T>
	Matrix3<T> Matrix3<T>::operator*(const Matrix3<T> &right) const
	{
		return multiplied(right);
	}
	template <typename T>
	Vector2<T> Matrix3<T>::operator*(const Vector2<T> &right) const
	{
		return Vector2<T>(
			el(0, 0) * right.x + el(1, 0) * right.y + el(2, 0),
			el(0, 1) * right.x + el(1, 1) * right.y + el(2, 1)
			);
	}
	template <typename T>
	Vector3<T> Matrix3<T>::operator*(const Vector3<T> &right) const
	{
		return Vector3<T>(
			el(0, 0) * right.x + el(1, 0) * right.y + el(2, 0) * right.z,
			el(0, 1) * right.x + el(1, 1) * right.y + el(2, 1) * right.z,
			el(0, 2) * right.x + el(1, 2) * right.y + el(2, 2) * right.z
			);
	}

	//Tyvm compiler for compiling this
	template struct Matrix3<float>;
	template struct Matrix3<double>;
	template struct Matrix3<int>;
	template struct Matrix3<long long>;
}
