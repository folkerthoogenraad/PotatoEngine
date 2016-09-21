#ifndef VEC3_H
#define VEC3_H

#include <iostream>

namespace ftec{

	template<typename T>
	struct vec3
	{
		T x, y, z;

		vec3(T x = 0, T y = 0, T z = 0);

		vec3<T>& add(const vec3<T>& other);
		vec3<T>& subtract(const vec3<T>& other);
		vec3<T>& divide(const vec3<T>& other);
		vec3<T>& multiply(const vec3<T>& other);

		vec3<T>& add(T other);
		vec3<T>& subtract(T other);
		vec3<T>& divide(T other);
		vec3<T>& multiply(T other);

		vec3<T>& normalize();
		T magnitude();

		static vec3<T>cross(const vec3<T>&left, const vec3<T>&right);
		static T dot(const vec3<T>&left, const vec3<T>&right);

		friend vec3<T>operator+(const vec3<T>& left, const vec3<T>& right);
		friend vec3<T>operator-(const vec3<T>& left, const vec3<T>& right);
		friend vec3<T>operator*(const vec3<T>& left, const vec3<T>& right);
		friend vec3<T>operator/(const vec3<T>& left, const vec3<T>& right);

		friend vec3<T>operator+(const vec3<T>& left, T right);
		friend vec3<T>operator-(const vec3<T>& left, T right);
		friend vec3<T>operator*(const vec3<T>& left, T right);
		friend vec3<T>operator/(const vec3<T>& left, T right);

		vec3<T>& operator+=(const vec3<T>& right);
		vec3<T>& operator-=(const vec3<T>& right);
		vec3<T>& operator*=(const vec3<T>& right);
		vec3<T>& operator/=(const vec3<T>& right);

		friend vec3<T>operator-(const vec3<T>& left);

        static const int COMPONENTS = 3;

		friend bool operator==(const vec3<T>& left, const vec3<T>& right);

		friend std::ostream& operator<<(std::ostream& left, const vec3<T>& right);

	};
	
	typedef vec3<float> vec3f;
	typedef vec3<int> vec3i;
	typedef vec3<double> vec3d;

}

#endif // VEC3_H
