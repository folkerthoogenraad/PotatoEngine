#pragma once

#include <array>

//TODO remove this dependency

//Huge TODO : optimize this
//The translations, as well as most of the scale and rotations can be done inplace
//No need for expensive full matrix matrix multiplcaiotn

//Also, the two matrix classes are the only two with a cpp file attached to them
//Maybe i should do this with more classes, I don't know

namespace ftec {


	template <typename T>
	struct Vector3;
	template <typename T>
	struct Vector4;

	template <typename T>
	struct Matrix4
	{
		union {
			std::array<T, 4 * 4> elements;
			struct {
				T a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
			};

			//[a b c d]
			//[e f g h]
			//[i j k l]
			//[m n o p]

		};

		Matrix4();
		Matrix4(std::array<T, 4 * 4> elements) : elements(elements) {}

		Matrix4<T>& multiply(const Matrix4& other);

		Vector4<T> multiply(const Vector4<T>& other) const;
		Vector3<T> multiply(const Vector3<T>& other) const;

		static Matrix4<T> identity();
		static Matrix4<T> orthographic(T l, T r, T b, T t, T n, T f);
		static Matrix4<T> perspective(T fov, T asp, T near, T far);
		static Matrix4<T> lookAt(const Vector3<T> &eye, const Vector3<T> &center, const Vector3<T> &up = Vector3<T>(0, 1, 0));
		static Matrix4<T> fromForward(const Vector3<T> &forward, const Vector3<T> &up);

		static Matrix4<T> translation(const Vector3<T>& translation);
		static Matrix4<T> rotation(T angle, const Vector3<T>& axis);
		static Matrix4<T> scale(const Vector3<T>& scale);

		static Matrix4<T> rotationX(T angle);
		static Matrix4<T> rotationY(T angle);
		static Matrix4<T> rotationZ(T angle);

		Matrix4<T> clone();

		Matrix4<T> transposed();
		Matrix4<T> &transpose();

		T determinant() const;

		inline T &el(int collumn, int row) { return elements[collumn + row * 4]; }
		inline T el(int collumn, int row) const { return elements[collumn + row * 4]; }

		//operators
		Matrix4<T> operator*(const Matrix4<T>& right);
		Matrix4<T> operator*=(const Matrix4<T>& right);

		Vector4<T> operator*(const Vector4<T>& right) const;
		Vector3<T> operator*(const Vector3<T>& right) const;
	};

	typedef Matrix4<float> Matrix4f;
	typedef Matrix4<double> Matrix4d;
}