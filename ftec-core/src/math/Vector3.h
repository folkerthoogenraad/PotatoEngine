#pragma once

namespace ftec{

	template<typename T>
	struct Vector2;

	template<typename T>
	struct Vector3
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
		Vector3(const Vector3<S> &other) : x((T)other.x), y((T)other.y), z((T)other.z) {};
		
		explicit Vector3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {};
		explicit Vector3(Vector2<T> v) : x(v.x), y(v.y), z(0) {};

		Vector3<T>& add(const Vector3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		Vector3<T>& subtract(const Vector3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		Vector3<T>& divide(const Vector3<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
		Vector3<T>& multiply(const Vector3<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		Vector3<T>& add(T other)
		{
			x += other;
			y += other;
			z += other;
			return *this;
		}
		Vector3<T>& subtract(T other)
		{
			x -= other;
			y -= other;
			z -= other;
			return *this;
		}
		Vector3<T>& divide(T other)
		{
			x /= other;
			y /= other;
			z /= other;
			return *this;
		}
		Vector3<T>& multiply(T other)
		{
			x *= other;
			y *= other;
			z *= other;
			return *this;
		}

		Vector3<T>& normalize()
		{
			T l = magnitude();
			if (l > 0) {
				x /= l;
				y /= l;
				z /= l;
			}
			return *this;
		}
		Vector3<T> normalized()const
		{
			return Vector3<T>(*this).normalize();
		}
		inline T magnitude() const
		{
			return (T)sqrt(sqrmagnitude());
		}
		inline T sqrmagnitude() const
		{
			return (T)x*x + y*y + z*z;
		}

		static Vector3<T>cross(const Vector3<T>&left, const Vector3<T>&right)
		{
			return Vector3<T>(
				left.y * right.z - left.z * right.y,
				left.z * right.x - left.x * right.z,
				left.x * right.y - left.y * right.x
				);
		}
		static T dot(const Vector3<T>&left, const Vector3<T>&right)
		{
			return left.x * right.x + left.y * right.y + left.z * right.z;
		}

		Vector3<T> operator+(const Vector3<T>& right) const
		{
			return Vector3(x + right.x, y + right.y, z + right.z);
		}
		Vector3<T> operator-(const Vector3<T>& right) const
		{
			return Vector3(x - right.x, y - right.y, z - right.z);
		}
		Vector3<T> operator*(const Vector3<T>& right) const
		{
			return Vector3(x * right.x, y * right.y, z * right.z);
		}
		Vector3<T> operator/(const Vector3<T>& right) const
		{
			return Vector3(x / right.x, y / right.y, z / right.z);
		}

		Vector3<T> operator+(T right) const
		{
			return Vector3(x + right, y + right, z + right);
		}
		Vector3<T> operator-(T right) const
		{
			return Vector3(x - right, y - right, z - right);
		}
		Vector3<T> operator*(T right) const
		{
			return Vector3(x * right, y * right, z * right);
		}
		Vector3<T> operator/(T right) const
		{
			return Vector3(x / right, y / right, z / right);
		}

		Vector3<T>& operator+=(const Vector3<T>& right)
		{
			return add(right);
		}
		Vector3<T>& operator-=(const Vector3<T>& right)
		{
			return subtract(right);
		}
		Vector3<T>& operator*=(const Vector3<T>& right)
		{
			return multiply(right);
		}
		Vector3<T>& operator/=(const Vector3<T>& right)
		{
			return divide(right);
		}

		Vector3<T>& operator+=(T right)
		{
			return add(right);
		}
		Vector3<T>& operator-=(T right)
		{
			return subtract(right);
		}
		Vector3<T>& operator*=(T right)
		{
			return multiply(right);
		}
		Vector3<T>& operator/=(T right)
		{
			return divide(right);
		}

		friend Vector3<T> operator+(T left, const Vector3<T>& right)
		{
			return Vector3(left + right.x, left + right.y, left + right.z);
		}
		friend Vector3<T> operator-(T left, const Vector3<T>& right)
		{
			return Vector3(left - right.x, left - right.y, left - right.z);
		}
		friend Vector3<T> operator*(T left, const Vector3<T>& right)
		{
			return Vector3(left * right.x, left * right.y, left * right.z);
		}
		friend Vector3<T> operator/(T left, const Vector3<T>& right)
		{
			return Vector3(left / right.x, left / right.y, left / right.z);
		}

		friend Vector3<T>operator-(const Vector3<T>& left)
		{
			return Vector3<T>(-left.x, -left.y, -left.z);
		}

        static const int COMPONENTS = 3;

		friend bool operator==(const Vector3<T>& left, const Vector3<T>& right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z;
		}
		friend bool operator<(const Vector3<T>& left, const Vector3<T>& right)
		{
			if (left.x < right.x)
				return true;
			if (left.x == right.x) {
				if (left.y < right.y)
					return true;
				if (left.y == right.y)
					return left.z < right.z;
			}

			return false;
				
			return left.x < right.x && left.y < right.y && left.z < right.z;
		}

		static Vector3<T> zero()
		{
			return Vector3<T>(0, 0, 0);
		}
		static Vector3<T> one()
		{
			return Vector3<T>(1, 1, 1);
		}

	};
	
	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
	typedef Vector3<double> Vector3d;
	typedef Vector3<long long> Vector3ll;

}
