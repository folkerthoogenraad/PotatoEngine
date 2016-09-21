#ifndef VEC2_H
#define VEC2_H

#include <iostream>

namespace ftec{


	template<typename T>
	struct vec2
	{
		T x, y;

		vec2(T x = 0, T y = 0);

		vec2<T>& add(const vec2<T>& other);
		vec2<T>& subtract(const vec2<T>& other);
		vec2<T>& divide(const vec2<T>& other);
		vec2<T>& multiply(const vec2<T>& other);


		friend vec2<T> operator+(const vec2<T>& left, const vec2<T>& right);
		friend vec2<T> operator-(const vec2<T>& left, const vec2<T>& right);
		friend vec2<T> operator*(const vec2<T>& left, const vec2<T>& right);
		friend vec2<T> operator/(const vec2<T>& left, const vec2<T>& right);

		vec2<T>& operator+=(const vec2<T>& right);
		vec2<T>& operator-=(const vec2<T>& right);
		vec2<T>& operator*=(const vec2<T>& right);
		vec2<T>& operator/=(const vec2<T>& right);


        static const int COMPONENTS = 2;

		friend bool operator==(const vec2<T>& left, const vec2<T>& right);

		friend std::ostream& operator<<(std::ostream& left, const vec2<T>& right);

	};

	typedef vec2<float> vec2f;
	typedef vec2<int> vec2i;
	typedef vec2<double> vec2d;

}


#endif
