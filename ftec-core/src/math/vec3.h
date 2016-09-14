#ifndef VEC3_H
#define VEC3_H

#include <iostream>

namespace ftec{

	struct vec3
	{
		float x, y, z;

		vec3(float x = 0, float y = 0, float z = 0);

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& divide(const vec3& other);
		vec3& multiply(const vec3& other);

		vec3& add(float other);
		vec3& subtract(float other);
		vec3& divide(float other);
		vec3& multiply(float other);

		vec3& normalize();
		float magnitude();

		friend vec3 operator+(const vec3& left, const vec3& right);
		friend vec3 operator-(const vec3& left, const vec3& right);
		friend vec3 operator*(const vec3& left, const vec3& right);
		friend vec3 operator/(const vec3& left, const vec3& right);

		friend vec3 operator+(const vec3& left, float right);
		friend vec3 operator-(const vec3& left, float right);
		friend vec3 operator*(const vec3& left, float right);
		friend vec3 operator/(const vec3& left, float right);

		vec3& operator+=(const vec3& right);
		vec3& operator-=(const vec3& right);
		vec3& operator*=(const vec3& right);
		vec3& operator/=(const vec3& right);

		friend vec3 operator-(const vec3& left);

        static const int COMPONENTS = 3;

		friend bool operator==(const vec3& left, const vec3& right);

		friend std::ostream& operator<<(std::ostream& left, const vec3& right);

	};

}

#endif // VEC3_H
