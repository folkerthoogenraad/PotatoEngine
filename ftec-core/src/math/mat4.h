#pragma once

#include "math.h"
#include <math.h>
#include <cstring>
#include <array>


namespace ftec {

	struct mat4
	{
		union {
			std::array<float, 4*4> elements;
			struct {
				float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
			};

			//[a b c d]
			//[e f g h]
			//[i j k l]
			//[m n o p]

		};

		mat4();
		mat4(std::array<float, 4 * 4> elements) : elements(elements) {}

		mat4& multiply(const mat4& other);

		vec4f multiply(const vec4f& other) const;
		vec3f multiply(const vec3f& other) const;

		static mat4 identity();
		static mat4 orthographic(float l, float r, float b, float t, float n, float f);
		static mat4 perspective(float fov, float asp, float near, float far);
		static mat4 lookAt(const vec3f &eye, const vec3f &center, const vec3f &up = vec3f(0, 1, 0));
		static mat4 fromForward(const vec3f &forward, const vec3f &up);

		static mat4 translation(const vec3f& translation);
		static mat4 rotation(float angle, const vec3f& axis);
		static mat4 scale(const vec3f& scale);

		static mat4 rotationX(float angle);
		static mat4 rotationY(float angle);
		static mat4 rotationZ(float angle);

		float determinant() const;

		inline float &el(int collumn, int row) { return elements[collumn + row * 4]; }
		inline float el(int collumn, int row) const { return elements[collumn + row * 4]; }

		//operators
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4 operator*=(const mat4& right);

		friend vec4f operator*(const mat4 &left, const vec4f& right);
		friend vec3f operator*(const mat4 &left, const vec3f& right);

		friend std::ostream& operator<<(std::ostream& left, const mat4& right);

	};
}
