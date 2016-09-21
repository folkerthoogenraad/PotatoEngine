#ifndef VEC4_H
#define VEC4_H

#include <iostream>

namespace ftec{



	struct vec4
	{
		float x, y, z, w;

		vec4(float x = 0, float y = 0, float z = 0, float w = 0);

		vec4& add(const vec4& other);
		vec4& subtract(const vec4& other);
		vec4& divide(const vec4& other);
		vec4& multiply(const vec4& other);


		friend vec4 operator+(const vec4& left, const vec4& right);
		friend vec4 operator-(const vec4& left, const vec4& right);
		friend vec4 operator*(const vec4& left, const vec4& right);
		friend vec4 operator/(const vec4& left, const vec4& right);

		vec4& operator+=(const vec4& right);
		vec4& operator-=(const vec4& right);
		vec4& operator*=(const vec4& right);
		vec4& operator/=(const vec4& right);


        static const int COMPONENTS = 4;


		friend bool operator==(const vec4& left, const vec4& right);

		friend std::ostream& operator<<(std::ostream& left, const vec4& right);

		inline static vec4 white() { return vec4(1, 1, 1, 1); }

	};

}

#endif // VEC4_H
