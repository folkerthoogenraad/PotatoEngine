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

	vec3& vec3::add(float other)
	{
		x += other;
		y += other;
		z += other;
		return *this;
	}

	vec3& vec3::subtract(float other)
	{
		x -= other;
		y -= other;
		z -= other;
		return *this;
	}

	vec3& vec3::divide(float other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	vec3& vec3::multiply(float other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	vec3 & vec3::normalize()
	{
		float l = magnitude();
		if (l > 0) {
			x /= l;
			y /= l;
			z /= l;
		}
		return *this;
	}

	float vec3::magnitude()
	{
		return (float) sqrt(x*x + y*y + z*z);
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

	vec3 operator+(const vec3& left, float right) {
		return vec3(left.x + right, left.y + right, left.z + right);
	}
	vec3 operator-(const vec3& left, float right) {
		return vec3(left.x - right, left.y - right, left.z - right);
	}
	vec3 operator*(const vec3& left, float right) {
		return vec3(left.x * right, left.y * right, left.z * right);
	}
	vec3 operator/(const vec3& left, float right) {
		return vec3(left.x / right, left.y / right, left.z / right);
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
