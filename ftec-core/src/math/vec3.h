#pragma once

namespace ftec{

	template<typename T>
	struct vec2;

	template<typename T>
	struct vec3
	{
		union {
			struct {
				T x, y, z;
			};
			struct {
				T r, g, b;
			};
			T v[3];
		};

		template<typename S>
		vec3(const vec3<S> &other) : x((T)other.x), y((T)other.y), z((T)other.z) {};
		
		explicit vec3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {};
		explicit vec3(vec2<T> v) : x(v.x), y(v.y), z(0) {};

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
		vec3<T> normalized()const
		{
			return vec3<T>(*this).normalize();
		}
		inline T magnitude() const
		{
			return (T)sqrt(sqrmagnitude());
		}
		inline T sqrmagnitude() const
		{
			return (T)x*x + y*y + z*z;
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

		vec3<T> operator+(const vec3<T>& right) const
		{
			return vec3(x + right.x, y + right.y, z + right.z);
		}
		vec3<T> operator-(const vec3<T>& right) const
		{
			return vec3(x - right.x, y - right.y, z - right.z);
		}
		vec3<T> operator*(const vec3<T>& right) const
		{
			return vec3(x * right.x, y * right.y, z * right.z);
		}
		vec3<T> operator/(const vec3<T>& right) const
		{
			return vec3(x / right.x, y / right.y, z / right.z);
		}

		vec3<T> operator+(T right) const
		{
			return vec3(x + right, y + right, z + right);
		}
		vec3<T> operator-(T right) const
		{
			return vec3(x - right, y - right, z - right);
		}
		vec3<T> operator*(T right) const
		{
			return vec3(x * right, y * right, z * right);
		}
		vec3<T> operator/(T right) const
		{
			return vec3(x / right, y / right, z / right);
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

		vec3<T>& operator+=(T right)
		{
			return add(right);
		}
		vec3<T>& operator-=(T right)
		{
			return subtract(right);
		}
		vec3<T>& operator*=(T right)
		{
			return multiply(right);
		}
		vec3<T>& operator/=(T right)
		{
			return divide(right);
		}

		friend vec3<T> operator+(T left, const vec3<T>& right)
		{
			return vec3(left + right.x, left + right.y, left + right.z);
		}
		friend vec3<T> operator-(T left, const vec3<T>& right)
		{
			return vec3(left - right.x, left - right.y, left - right.z);
		}
		friend vec3<T> operator*(T left, const vec3<T>& right)
		{
			return vec3(left * right.x, left * right.y, left * right.z);
		}
		friend vec3<T> operator/(T left, const vec3<T>& right)
		{
			return vec3(left / right.x, left / right.y, left / right.z);
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
		friend bool operator<(const vec3<T>& left, const vec3<T>& right)
		{
			return left.x < right.x && left.y < right.y && left.z < right.z;
		}

		static vec3<T> zero()
		{
			return vec3<T>(0, 0, 0);
		}
		static vec3<T> one()
		{
			return vec3<T>(1, 1, 1);
		}

	};
	
	typedef vec3<float> vec3f;
	typedef vec3<int> vec3i;
	typedef vec3<double> vec3d;

}
