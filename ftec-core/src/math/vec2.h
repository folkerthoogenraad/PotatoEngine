#ifndef VEC2_H
#define VEC2_H


#include <iostream>

namespace ftec{



	struct vec2
	{
		float x, y;

		vec2(float x = 0, float y = 0);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& divide(const vec2& other);
		vec2& multiply(const vec2& other);


		friend vec2 operator+(const vec2& left, const vec2& right);
		friend vec2 operator-(const vec2& left, const vec2& right);
		friend vec2 operator*(const vec2& left, const vec2& right);
		friend vec2 operator/(const vec2& left, const vec2& right);

		vec2& operator+=(const vec2& right);
		vec2& operator-=(const vec2& right);
		vec2& operator*=(const vec2& right);
		vec2& operator/=(const vec2& right);


        static const int COMPONENTS = 2;


		friend bool operator==(const vec2& left, const vec2& right);

		friend std::ostream& operator<<(std::ostream& left, const vec2& right);

	};

}


#endif
