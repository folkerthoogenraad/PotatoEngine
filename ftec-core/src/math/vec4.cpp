#include "math/vec4.h"

namespace ftec{

	vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	vec4& vec4::add(const vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vec4& vec4::subtract(const vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vec4& vec4::divide(const vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	vec4& vec4::multiply(const vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}


	vec4 operator+(const vec4& left, const vec4& right){
		return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}
	vec4 operator-(const vec4& left, const vec4& right){
		return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}
	vec4 operator*(const vec4& left, const vec4& right){
		return vec4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}
	vec4 operator/(const vec4& left, const vec4& right){
		return vec4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
	}


	vec4& vec4::operator+=(const vec4& right){
		return add(right);
	}
	vec4& vec4::operator-=(const vec4& right){
		return subtract(right);
	}
	vec4& vec4::operator*=(const vec4& right){
		return multiply(right);
	}
	vec4& vec4::operator/=(const vec4& right){
		return divide(right);
	}


	bool operator==(const vec4& left, const vec4& right){
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}
	std::ostream& operator<<(std::ostream& left, const vec4& right){
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ", " << right.w << ")";
	}
}
