#ifndef VEC4_H
#define VEC4_H

#include <iostream>

namespace ftec{



	template<typename T>
	struct vec4
	{
		T x, y, z, w;

		vec4(T x = 0, T y = 0, T z = 0, T w = 0);

		vec4<T>&  add(const vec4<T>&  other);
		vec4<T>&  subtract(const vec4<T>&  other);
		vec4<T>&  divide(const vec4<T>&  other);
		vec4<T>&  multiply(const vec4<T>&  other);


		friend vec4<T> operator+(const vec4<T>&  left, const vec4<T>&  right);
		friend vec4<T> operator-(const vec4<T>&  left, const vec4<T>&  right);
		friend vec4<T> operator*(const vec4<T>&  left, const vec4<T>&  right);
		friend vec4<T> operator/(const vec4<T>&  left, const vec4<T>&  right);

		vec4<T>&  operator+=(const vec4<T>&  right);
		vec4<T>&  operator-=(const vec4<T>&  right);
		vec4<T>&  operator*=(const vec4<T>&  right);
		vec4<T>&  operator/=(const vec4<T>&  right);


        static const int COMPONENTS = 4;


		friend bool operator==(const vec4<T>&  left, const vec4<T>&  right);

		friend std::ostream& operator<<(std::ostream& left, const vec4<T>&  right);

		inline static vec4<T> white() { return vec4(1, 1, 1, 1); }

	};

	typedef vec4<float> vec4f;
	typedef vec4<int> vec4i;
	typedef vec4<double> vec4d;

}

#endif // VEC4_H
