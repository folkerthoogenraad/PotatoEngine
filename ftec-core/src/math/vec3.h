#pragma once

#include <iostream>

namespace ftec{

	template<typename T>
	struct vec3
	{
		T x, y, z;

		vec3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {};

		vec3<T>& add(const vec3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		vec3<T>& subtract(const vec3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		vec3<T>& divide(const vec3<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
		vec3<T>& multiply(const vec3<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		vec3<T>& add(T other)
		{
			x += other;
			y += other;
			z += other;
			return *this;
		}

		vec3<T>& subtract(T other)
		{
			x -= other;
			y -= other;
			z -= other;
			return *this;
		}
		vec3<T>& divide(T other)
		{
			x /= other;
			y /= other;
			z /= other;
			return *this;
		}
		vec3<T>& multiply(T other)
		{
			x *= other;
			y *= other;
			z *= other;
			return *this;
		}

		vec3<T>& normalize()
		{
			T l = magnitude();
			if (l > 0) {
				x /= l;
				y /= l;
				z /= l;
			}
			return *this;
		}
		T magnitude()
		{
			return (T)sqrt(x*x + y*y + z*z);
		}

		static vec3<T>cross(const vec3<T>&left, const vec3<T>&right)
		{
			return vec3<T>(
				left.y * right.z - left.z * right.y,
				left.z * right.x - left.x * right.z,
				left.x * right.y - left.y * right.x
				);
		}
		static T dot(const vec3<T>&left, const vec3<T>&right)
		{
			return left.x * right.x + left.y * right.y + left.z * right.z;
		}

		friend vec3<T>operator+(const vec3<T>& left, const vec3<T>& right)
		{
			return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
		}
		friend vec3<T>operator-(const vec3<T>& left, const vec3<T>& right)
		{
			return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
		}
		friend vec3<T>operator*(const vec3<T>& left, const vec3<T>& right)
		{
			return vec3(left.x * right.x, left.y * right.y, left.z * right.z);
		}
		friend vec3<T>operator/(const vec3<T>& left, const vec3<T>& right)
		{
			return vec3(left.x / right.x, left.y / right.y, left.z / right.z);
		}

		friend vec3<T>operator+(const vec3<T>& left, T right)
		{
			return vec3(left.x + right, left.y + right, left.z + right);
		}
		friend vec3<T>operator-(const vec3<T>& left, T right)
		{
			return vec3(left.x - right, left.y - right, left.z - right);
		}
		friend vec3<T>operator*(const vec3<T>& left, T right)
		{
			return vec3(left.x * right, left.y * right, left.z * right);
		}
		friend vec3<T>operator/(const vec3<T>& left, T right)
		{
			return vec3(left.x / right, left.y / right, left.z / right);
		}

		vec3<T>& operator+=(const vec3<T>& right)
		{
			return add(right);
		}
		vec3<T>& operator-=(const vec3<T>& right)
		{
			return subtract(right);
		}
		vec3<T>& operator*=(const vec3<T>& right)
		{
			return multiply(right);
		}
		vec3<T>& operator/=(const vec3<T>& right)
		{
			return divide(right);
		}

		friend vec3<T>operator-(const vec3<T>& left)
		{
			return vec3<T>(-left.x, -left.y, -left.z);
		}

        static const int COMPONENTS = 3;

		friend bool operator==(const vec3<T>& left, const vec3<T>& right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z;
		}

		friend std::ostream& operator<<(std::ostream& left, const vec3<T>& right)
		{
			return left << "(" << right.x << ", " << right.y << ", " << right.z << ")";
		}

	};
	
	typedef vec3<float> vec3f;
	typedef vec3<int> vec3i;
	typedef vec3<double> vec3d;

}
