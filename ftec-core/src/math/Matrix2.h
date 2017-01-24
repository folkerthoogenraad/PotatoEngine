#pragma once

#include <array>

namespace ftec {
	template<typename T>
	struct Matrix2
	{
		union {
			std::array<T, 2 * 2> elements;

			struct {
				T a, b, c, d;
			};
		};

		Matrix2()
		{
			std::fill(elements.begin(), elements.end(), (T)0);
			elements[0 + 0 * 1] = (T)1;
			elements[1 + 1 * 1] = (T)1;
		}
		Matrix2(std::array<T, 2 * 2> elements) : elements(elements) {}

		Matrix2(const Matrix2<T> &other) : elements(other.elements) {}
		Matrix2(Matrix2<T> &&other) : elements(std::move(other.elements)){}

		~Matrix2()
		{
			elements.~array<T, 2 * 2>();
		}

		Matrix2<T> &multiply(const Matrix2<T> &m)
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
		Matrix2<T> multiplied(const Matrix2<T> &m) const
		{
			return clone().multiply(m);
		}

		Matrix2<T> &transpose()
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
		Matrix2<T> transposed() const
		{
			return clone().transpose();
		}

		Matrix2<T> &inverse()
		{
			return *this;
		}

		Matrix2<T> inversed() const
		{
			return clone().inverse();
		}

		Matrix2<T> clone() const
		{
			return Matrix2<T>(*this);
		}

		T determinant() const
		{
			return a * d - b * c;
		}

		Matrix2<T> &operator *=(const Matrix2<T> other)
		{
			return multiply(other);
		}
		Matrix2<T> operator*(const Matrix2<T> &right) const
		{
			return multiplied(right);
		}
		Matrix2<T> &operator=(const Matrix2<T> other)
		{
			elements = other.elements;
			return *this;
		}

		inline T &el(int column, int row) { return elements[column + row * 3]; }
		inline T el(int column, int row) const { return elements[column + row * 3]; }
	};

	typedef Matrix2<float> Matrix2f;
	typedef Matrix2<double> Matrix2d;
	typedef Matrix2<int> Matrix2i;
	typedef Matrix2<long long> Matrix2ll;
}