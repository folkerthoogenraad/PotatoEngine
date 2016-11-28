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
	struct vec3;
	template <typename T>
	struct vec4;

	template <typename T>
	struct mat4
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

		mat4();
		mat4(std::array<T, 4 * 4> elements) : elements(elements) {}

		mat4<T>& multiply(const mat4& other);

		vec4<T> multiply(const vec4<T>& other) const;
		vec3<T> multiply(const vec3<T>& other) const;

		static mat4<T> identity();
		static mat4<T> orthographic(T l, T r, T b, T t, T n, T f);
		static mat4<T> perspective(T fov, T asp, T near, T far);
		static mat4<T> lookAt(const vec3<T> &eye, const vec3<T> &center, const vec3<T> &up = vec3<T>(0, 1, 0));
		static mat4<T> fromForward(const vec3<T> &forward, const vec3<T> &up);

		static mat4<T> translation(const vec3<T>& translation);
		static mat4<T> rotation(T angle, const vec3<T>& axis);
		static mat4<T> scale(const vec3<T>& scale);

		static mat4<T> rotationX(T angle);
		static mat4<T> rotationY(T angle);
		static mat4<T> rotationZ(T angle);

		T determinant() const;

		inline T &el(int collumn, int row) { return elements[collumn + row * 4]; }
		inline T el(int collumn, int row) const { return elements[collumn + row * 4]; }

		//operators
		mat4<T> operator*(const mat4<T>& right);
		mat4<T> operator*=(const mat4<T>& right);

		vec4<T> operator*(const vec4<T>& right) const;
		vec3<T> operator*(const vec3<T>& right) const;
	};

	typedef mat4<float> mat4f;
	typedef mat4<double> mat4d;
	typedef mat4<int> mat4i;
}