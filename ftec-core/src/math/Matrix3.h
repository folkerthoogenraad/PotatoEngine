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

		Matrix3()
		{
			std::fill(elements.begin(), elements.end(), (T)0);
			elements[0 + 0 * 3] = (T)1;
			elements[1 + 1 * 3] = (T)1;
			elements[2 + 2 * 3] = (T)1;
		}
		Matrix3(std::array<T, 3 * 3> elements) : elements(elements) {}

		Matrix3(const Matrix3<T> &other) : elements(other.elements) {}
		Matrix3(Matrix3<T> &&other) : elements(std::move(other.elements)) {}

		~Matrix3()
		{
			elements.~array<T, 3 * 3>();
		}

		Matrix3<T> &translate(T x, T y)
		{
			multiply(Matrix3<T>({
				1,0,x,
				0,1,y,
				0,0,1,
			}));
			return *this;
		}
		Matrix3<T> &scale(T x, T y)
		{
			multiply(Matrix3<T>({
				x,0,0,
				0,y,0,
				0,0,1,
			}));
			return *this;
		}
		Matrix3<T> &rotate(T x)
		{
			T r = angle * ((T)3.141592654 / (T)180.0);
			T s = (T)sin(r);
			T c = (T)cos(r);

			multiply(Matrix3<T>({
				c,-s,0,
				s,c,0,
				0,0,1,
			}));

			return *this;
		}

		Matrix3<T> &multiply(const Matrix3<T> &m)
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
		Matrix3<T> multiplied(const Matrix3<T> &m) const
		{
			return clone().multiply(m);
		}

		Matrix3<T> &multiply(const T &t)
		{
			for (int i = 0; i < elements.size(); i++) {
				elements[i] *= t;
			}
			return *this;
		}
		Matrix3<T> multiplied(const T &t) const
		{
			return clone().multiply(t);
		}

		Matrix3<T> &transpose()
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
		Matrix3<T> transposed() const
		{
			return clone().transpose();
		}

		Matrix3<T> &inverse()
		{
			T d = determinant();

			return multiply((T)1.0 / d);
		}
		Matrix3<T> inversed() const
		{
			return clone().inverse();
		}

		Matrix3<T> clone() const
		{
			return Matrix3<T>(*this);
		}

		Matrix4<T> expand() const
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

		T determinant() const
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

		static Matrix3<T> identity()
		{
			return Matrix3<T>();
		}
		static Matrix3<T> translation(T x, T y)
		{
			return Matrix3<T>().translate(x, y);
		}
		static Matrix3<T> scaled(T x, T y)
		{
			return Matrix3<T>().scale(x, y);
		}
		static Matrix3<T> rotation(T x)
		{
			return Matrix3<T>().rotate(x);
		}

		static Matrix3<T> translation(Vector2<T> v)
		{
			return translation(v.x, v.y);
		}
		static Matrix3<T> scaled(Vector2<T> v)
		{
			return scaled(v.x, v.y);
		}

		Matrix3<T> &operator *=(const Matrix3<T> other)
		{
			return multiply(other);
		}

		Matrix3<T> operator*(const Matrix3<T> &right) const
		{
			return multiplied(right);
		}
		Vector2<T> operator*(const Vector2<T> &right) const
		{
			return Vector2<T>(
				el(0, 0) * right.x + el(1, 0) * right.y + el(2, 0),
				el(0, 1) * right.x + el(1, 1) * right.y + el(2, 1)
				);
		}
		Vector3<T> operator*(const Vector3<T> &right) const
		{
			return Vector3<T>(
				el(0, 0) * right.x + el(1, 0) * right.y + el(2, 0) * right.z,
				el(0, 1) * right.x + el(1, 1) * right.y + el(2, 1) * right.z,
				el(0, 2) * right.x + el(1, 2) * right.y + el(2, 2) * right.z
				);
		}

		Matrix3<T> &operator =(const Matrix3<T> &other)
		{
			elements = other.elements;
			return *this;
		}

		inline T &el(int column, int row) { return elements[column + row * 3]; }
		inline T el(int column, int row) const { return elements[column + row * 3]; }
	};

	typedef Matrix3<float> Matrix3f;
	typedef Matrix3<double> Matrix3d;
	typedef Matrix3<int> Matrix3i;
	typedef Matrix3<long long> Matrix3ll;
}