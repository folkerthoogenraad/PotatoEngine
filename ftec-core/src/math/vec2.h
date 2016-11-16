#pragma once

#include <iostream>
#include <array>

namespace ftec {

	template<typename T>
	struct vec2
	{
		union {
			struct {
				T x, y;
			};
			struct {
				T width, height;
			};
			std::array<T, 2> v;
		};

		template<typename S>
		vec2(const vec2<S> &other) : x((T)other.x), y((T)other.y) {};

		explicit vec2(T x = 0, T y = 0) : x(x), y(y) {};

		vec2<T>& add(const vec2<T>& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		vec2<T>& subtract(const vec2<T>& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		vec2<T>& divide(const vec2<T>& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		vec2<T>& multiply(const vec2<T>& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		vec2<T>& add(T other)
		{
			x += other;
			y += other;
			return *this;
		}
		vec2<T>& subtract(T other)
		{
			x -= other;
			y -= other;
			return *this;
		}
		vec2<T>& divide(T other)
		{
			x /= other;
			y /= other;
			return *this;
		}
		vec2<T>& multiply(T other)
		{
			x *= other;
			y *= other;
			return *this;
		}

		vec2<T>& normalize()
		{
			T l = magnitude();
			if (l > 0) {
				x /= l;
				y /= l;
			}
			return *this;
		}
		T magnitude()
		{
			return (T)sqrt(x*x + y*y);
		}

		static T dot(const vec2<T>&left, const vec2<T>&right)
		{
			return left.x * right.x + left.y * right.y;
		}
		static T cross(const vec2<T>&left, const vec2<T>&right)
		{
			return left.x*right.y - left.y*right.x;
		}
		static vec2<T> perp(const vec2<T>&left)
		{
			return vec2<T>(left.y, -left.x);
		}

		vec2<T> operator+(const vec2<T>& right) const
		{
			return vec2(x + right.x, y + right.y);
		}
		vec2<T> operator-(const vec2<T>& right) const
		{
			return vec2(x - right.x, y - right.y);
		}
		vec2<T> operator*(const vec2<T>& right) const
		{
			return vec2(x * right.x, y * right.y);
		}
		vec2<T> operator/(const vec2<T>& right) const
		{
			return vec2(x / right.x, y / right.y);
		}

		vec2<T> operator+(T right) const
		{
			return vec2(x + right, y + right);
		}
		vec2<T> operator-(T right) const
		{
			return vec2(x - right, y - right);
		}
		vec2<T> operator*(T right) const
		{
			return vec2(x * right, y * right);
		}
		vec2<T> operator/(T right) const
		{
			return vec2(x / right, y / right);
		}

		vec2<T>& operator+=(const vec2<T>& right)
		{
			return add(right);
		}
		vec2<T>& operator-=(const vec2<T>& right)
		{
			return subtract(right);
		}
		vec2<T>& operator*=(const vec2<T>& right)
		{
			return multiply(right);
		}
		vec2<T>& operator/=(const vec2<T>& right)
		{
			return divide(right);
		}

		vec2<T>& operator+=(T right)
		{
			return add(right);
		}
		vec2<T>& operator-=(T right)
		{
			return subtract(right);
		}
		vec2<T>& operator*=(T right)
		{
			return multiply(right);
		}
		vec2<T>& operator/=(T right)
		{
			return divide(right);
		}

		friend vec2<T> operator+(T left, const vec2<T> right)
		{
			return vec2(left + right.x, left + right.y);
		}
		friend vec2<T> operator-(T left, const vec2<T> right)
		{
			return vec2(left - right.x, left - right.y);
		}
		friend vec2<T> operator*(T left, const vec2<T> right)
		{
			return vec2(left * right.x, left * right.y);
		}
		friend vec2<T> operator/(T left, const vec2<T> right)
		{
			return vec2(left / right.x, left / right.y);
		}

		friend vec2<T>operator-(const vec2<T>& left)
		{
			return vec2<T>(-left.x, -left.y);
		}
		
		static const int COMPONENTS = 2;

		friend bool operator==(const vec2<T>& left, const vec2<T>& right)
		{
			return left.x == right.x && left.y == right.y;
		}
		friend std::ostream& operator<<(std::ostream& left, const vec2<T>& right)
		{
			return left << "(" << right.x << ", " << right.y << ")";
		}

		friend bool operator <(const vec2<T>& left, const vec2<T>& right)
		{
			if (left.x < right.x)
				return true;
			if (left.x == right.x) {
				return left.y < right.y;
			}
			else {
				return false;
			}
		}
	
};

	typedef vec2<float> vec2f;
	typedef vec2<int> vec2i;
	typedef vec2<double> vec2d;

}
