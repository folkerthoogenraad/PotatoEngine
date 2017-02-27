#pragma once

namespace ftec {

	//Forward declare for the typedefs
	template<typename T> struct Vector4;

	typedef Vector4<float> Vector4f;
	typedef Vector4<int> Vector4i;
	typedef Vector4<double> Vector4d;

	typedef Vector4<float> Color;
	typedef Vector4<uint8_t> Color32;

	//Implementation here
	template<typename T>
	struct Vector4
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
		Vector4(const Vector4<S> &other) : x((T)other.x), y((T)other.y), z((T)other.z), w((T)other.w) {};
		explicit Vector4(T x = 0, T y = 0, T z = 0, T w = 0) : x(x), y(y), z(z), w(w) {};

		Vector4<T>& add(const Vector4<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		Vector4<T>& subtract(const Vector4<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}
		Vector4<T>& divide(const Vector4<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}
		Vector4<T>& multiply(const Vector4<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		Vector4<T>& add(T other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
			return *this;
		}
		Vector4<T>& subtract(T other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
			return *this;
		}
		Vector4<T>& divide(T other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
			return *this;
		}
		Vector4<T>& multiply(T other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;
		}

		Vector4<T>& normalize()
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
		
		static T dot(const Vector4<T>&left, const Vector4<T>&right)
		{
			return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
		}

		friend Vector4<T>operator+(const Vector4<T>& left, const Vector4<T>& right)
		{
			return Vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
		}
		friend Vector4<T>operator-(const Vector4<T>& left, const Vector4<T>& right)
		{
			return Vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
		}
		friend Vector4<T>operator*(const Vector4<T>& left, const Vector4<T>& right)
		{
			return Vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
		}
		friend Vector4<T>operator/(const Vector4<T>& left, const Vector4<T>& right)
		{
			return Vector4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
		}

		friend Vector4<T>operator+(const Vector4<T>& left, T right)
		{
			return Vector4(left.x + right, left.y + right, left.z + right, left.w + right);
		}
		friend Vector4<T>operator-(const Vector4<T>& left, T right)
		{
			return Vector4(left.x - right, left.y - right, left.z - right, left.w - right);
		}
		friend Vector4<T>operator*(const Vector4<T>& left, T right)
		{
			return Vector4(left.x * right, left.y * right, left.z * right, left.w * right);
		}
		friend Vector4<T>operator/(const Vector4<T>& left, T right)
		{
			return Vector4(left.x / right, left.y / right, left.z / right, left.w / right);
		}

		Vector4<T>& operator+=(const Vector4<T>& right)
		{
			return add(right);
		}
		Vector4<T>& operator-=(const Vector4<T>& right)
		{
			return subtract(right);
		}
		Vector4<T>& operator*=(const Vector4<T>& right)
		{
			return multiply(right);
		}
		Vector4<T>& operator/=(const Vector4<T>& right)
		{
			return divide(right);
		}

		friend Vector4<T>operator-(const Vector4<T>& left)
		{
			return Vector4<T>(-left.x, -left.y, -left.z, -left.w);
		}

		static const int COMPONENTS = 3;

		friend bool operator==(const Vector4<T>& left, const Vector4<T>& right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
		}

		inline static Color32 white() { return Color32(255, 255, 255, 255); }
		inline static Color32 red() { return Color32(255, 0, 0, 255); }
		inline static Color32 green() { return Color32(0, 255, 0, 255); }
		inline static Color32 blue() { return Color32(0, 0, 255, 255); }
		inline static Color32 black() { return Color32(0, 0, 0, 255); }
		inline static Color32 yellow() { return Color32(255, 255, 0, 255); }
		inline static Color32 cyan() { return Color32(0, 255, 255, 255); }


		inline static Color32 dkgray() { return Color32(50, 50, 50, 255); }

	};

	

}
