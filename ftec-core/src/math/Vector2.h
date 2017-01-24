#pragma once

namespace ftec {

	template<typename T>
	struct Vector2
	{
		union {
			struct {
				T x, y;
			};
			struct {
				T width, height;
			};
			T v[2];
		};

		template<typename S>
		Vector2(const Vector2<S> &other) : x((T)other.x), y((T)other.y) {};

		explicit Vector2(T x = 0, T y = 0) : x(x), y(y) {};

		Vector2(const Vector2<T> &other) : x(other.x), y(other.y){}
		Vector2(Vector2<T> &&other) : x(std::move(other.x)), y(std::move(other.y)){}

		~Vector2()
		{
			x.~T();
			y.~T();
		}


		Vector2<T>& add(const Vector2<T>& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Vector2<T>& subtract(const Vector2<T>& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		Vector2<T>& divide(const Vector2<T>& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		Vector2<T>& multiply(const Vector2<T>& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		Vector2<T>& add(T other)
		{
			x += other;
			y += other;
			return *this;
		}
		Vector2<T>& subtract(T other)
		{
			x -= other;
			y -= other;
			return *this;
		}
		Vector2<T>& divide(T other)
		{
			x /= other;
			y /= other;
			return *this;
		}
		Vector2<T>& multiply(T other)
		{
			x *= other;
			y *= other;
			return *this;
		}

		Vector2<T>& normalize()
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
		T sqrmagnitude()
		{
			return (T) x*x + y*y;
		}

		static T dot(const Vector2<T>&left, const Vector2<T>&right)
		{
			return left.x * right.x + left.y * right.y;
		}
		static T cross(const Vector2<T>&left, const Vector2<T>&right)
		{
			return left.x*right.y - left.y*right.x;
		}
		static Vector2<T> perp(const Vector2<T>&left)
		{
			return Vector2<T>(left.y, -left.x);
		}

		Vector2<T> operator+(const Vector2<T>& right) const
		{
			return Vector2(x + right.x, y + right.y);
		}
		Vector2<T> operator-(const Vector2<T>& right) const
		{
			return Vector2(x - right.x, y - right.y);
		}
		Vector2<T> operator*(const Vector2<T>& right) const
		{
			return Vector2(x * right.x, y * right.y);
		}
		Vector2<T> operator/(const Vector2<T>& right) const
		{
			return Vector2(x / right.x, y / right.y);
		}

		Vector2<T> operator+(T right) const
		{
			return Vector2(x + right, y + right);
		}
		Vector2<T> operator-(T right) const
		{
			return Vector2(x - right, y - right);
		}
		Vector2<T> operator*(T right) const
		{
			return Vector2(x * right, y * right);
		}
		Vector2<T> operator/(T right) const
		{
			return Vector2(x / right, y / right);
		}

		Vector2<T>& operator+=(const Vector2<T>& right)
		{
			return add(right);
		}
		Vector2<T>& operator-=(const Vector2<T>& right)
		{
			return subtract(right);
		}
		Vector2<T>& operator*=(const Vector2<T>& right)
		{
			return multiply(right);
		}
		Vector2<T>& operator/=(const Vector2<T>& right)
		{
			return divide(right);
		}

		Vector2<T>& operator+=(T right)
		{
			return add(right);
		}
		Vector2<T>& operator-=(T right)
		{
			return subtract(right);
		}
		Vector2<T>& operator*=(T right)
		{
			return multiply(right);
		}
		Vector2<T>& operator/=(T right)
		{
			return divide(right);
		}

		friend Vector2<T> operator+(T left, const Vector2<T> right)
		{
			return Vector2(left + right.x, left + right.y);
		}
		friend Vector2<T> operator-(T left, const Vector2<T> right)
		{
			return Vector2(left - right.x, left - right.y);
		}
		friend Vector2<T> operator*(T left, const Vector2<T> right)
		{
			return Vector2(left * right.x, left * right.y);
		}
		friend Vector2<T> operator/(T left, const Vector2<T> right)
		{
			return Vector2(left / right.x, left / right.y);
		}

		friend Vector2<T>operator-(const Vector2<T>& left)
		{
			return Vector2<T>(-left.x, -left.y);
		}

		Vector2<T>& operator=(const Vector2<T>& right)
		{
			x = right.x;
			y = right.y;
			return *this;
		}
		
		static const int COMPONENTS = 2;

		friend bool operator==(const Vector2<T>& left, const Vector2<T>& right)
		{
			return left.x == right.x && left.y == right.y;
		}

		friend bool operator <(const Vector2<T>& left, const Vector2<T>& right)
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

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<double> Vector2d;
	typedef Vector2<long long> Vector2ll;

}
