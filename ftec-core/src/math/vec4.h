#pragma once

#include <iostream>

namespace ftec {

	//Forward declare for the typedefs
	template<typename T> struct vec4;

	typedef vec4<float> vec4f;
	typedef vec4<int> vec4i;
	typedef vec4<double> vec4d;

	typedef vec4<float> color;
	typedef vec4<unsigned char> color32;

	//Implementation here
	template<typename T>
	struct vec4
	{
		union {
			struct {
				T x, y, z, w;
			};
			struct {
				T r, g, b, a;
			};
			T v[4];
		};
		

		template<typename S>
		vec4(const vec4<S> &other) : x((T)other.x), y((T)other.y), z((T)other.z), w((T)other.w) {};
		vec4(T x = 0, T y = 0, T z = 0, T w = 0) : x(x), y(y), z(z), w(w) {};

		vec4<T>& add(const vec4<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		vec4<T>& subtract(const vec4<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}
		vec4<T>& divide(const vec4<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}
		vec4<T>& multiply(const vec4<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		vec4<T>& add(T other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
			return *this;
		}

		vec4<T>& subtract(T other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
			return *this;
		}
		vec4<T>& divide(T other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
			return *this;
		}
		vec4<T>& multiply(T other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;
		}

		vec4<T>& normalize()
		{
			T l = magnitude();
			if (l > 0) {
				x /= l;
				y /= l;
				z /= l;
				w /= l;
			}
			return *this;
		}
		T magnitude()
		{
			return (T)sqrt(x*x + y*y + z*z + w*w);
		}
		static T dot(const vec4<T>&left, const vec4<T>&right)
		{
			return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
		}

		friend vec4<T>operator+(const vec4<T>& left, const vec4<T>& right)
		{
			return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
		}
		friend vec4<T>operator-(const vec4<T>& left, const vec4<T>& right)
		{
			return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
		}
		friend vec4<T>operator*(const vec4<T>& left, const vec4<T>& right)
		{
			return vec4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
		}
		friend vec4<T>operator/(const vec4<T>& left, const vec4<T>& right)
		{
			return vec4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
		}

		friend vec4<T>operator+(const vec4<T>& left, T right)
		{
			return vec4(left.x + right, left.y + right, left.z + right, left.w + right);
		}
		friend vec4<T>operator-(const vec4<T>& left, T right)
		{
			return vec4(left.x - right, left.y - right, left.z - right, left.w - right);
		}
		friend vec4<T>operator*(const vec4<T>& left, T right)
		{
			return vec4(left.x * right, left.y * right, left.z * right, left.w * right);
		}
		friend vec4<T>operator/(const vec4<T>& left, T right)
		{
			return vec4(left.x / right, left.y / right, left.z / right, left.w / right);
		}

		vec4<T>& operator+=(const vec4<T>& right)
		{
			return add(right);
		}
		vec4<T>& operator-=(const vec4<T>& right)
		{
			return subtract(right);
		}
		vec4<T>& operator*=(const vec4<T>& right)
		{
			return multiply(right);
		}
		vec4<T>& operator/=(const vec4<T>& right)
		{
			return divide(right);
		}

		friend vec4<T>operator-(const vec4<T>& left)
		{
			return vec4<T>(-left.x, -left.y, -left.z, -left.w);
		}

		static const int COMPONENTS = 3;

		friend bool operator==(const vec4<T>& left, const vec4<T>& right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
		}

		friend std::ostream& operator<<(std::ostream& left, const vec4<T>& right)
		{
			return left << "(" << right.x << ", " << right.y << ", " << right.z << ", " << right.w << ")";
		}

		inline static color32 white() { return color32(255, 255, 255, 255); }
		inline static color32 red() { return color32(255, 0, 0, 255); }
		inline static color32 green() { return color32(0, 255, 0, 255); }
		inline static color32 blue() { return color32(0, 0, 255, 255); }
		inline static color32 black() { return color32(0,0,0,255); }


		inline static color32 dkgray() { return color32(50, 50, 50, 255); }

	};

	

}
