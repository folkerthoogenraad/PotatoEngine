#pragma once

#include "math.h"
#include <math.h>
#include <cstring>


namespace ftec {

	struct mat4
	{
		float elements[4 * 4];

		mat4();

		mat4& multiply(const mat4& other);

		vec4 multiply(const vec4& other) const;
		vec3 multiply(const vec3& other) const;

		static mat4 identity();
		static mat4 orthographic(float l, float r, float b, float t, float n, float f);
		static mat4 perspective(float fov, float asp, float near, float far);
		static mat4 lookAt(const vec3 &eye, const vec3 &center, const vec3 &up = vec3(0, 1, 0));

		static mat4 translation(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

		static mat4 rotationX(float angle);
		static mat4 rotationY(float angle);
		static mat4 rotationZ(float angle);

		//operators
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4 operator*=(const mat4& right);

		friend vec4 operator*(const mat4 &left, const vec4& right);
		friend vec3 operator*(const mat4 &left, const vec3& right);

		friend std::ostream& operator<<(std::ostream& left, const mat4& right);

	};
}
