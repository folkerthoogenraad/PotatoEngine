#include "math/vec3.h"

namespace ftec{

	vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {};

	vec3& vec3::add(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::subtract(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::divide(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	vec3& vec3::multiply(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}


	vec3 operator+(const vec3& left, const vec3& right){
		return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}
	vec3 operator-(const vec3& left, const vec3& right){
		return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}
	vec3 operator*(const vec3& left, const vec3& right){
		return vec3(left.x * right.x, left.y * right.y, left.z * right.z);
	}
	vec3 operator/(const vec3& left, const vec3& right){
		return vec3(left.x / right.x, left.y / right.y, left.z / right.z);
	}


	vec3& vec3::operator+=(const vec3& right){
		return add(right);
	}
	vec3& vec3::operator-=(const vec3& right){
		return subtract(right);
	}
	vec3& vec3::operator*=(const vec3& right){
		return multiply(right);
	}
	vec3& vec3::operator/=(const vec3& right){
		return divide(right);
	}

	vec3 operator-(const vec3 & left)
	{
		return vec3(-left.x, -left.y, -left.z);
	}

	bool operator==(const vec3& left, const vec3& right){
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}
	std::ostream& operator<<(std::ostream& left, const vec3& right){
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ")";
	}
}
