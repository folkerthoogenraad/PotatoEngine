#include "math/vec2.h"

namespace ftec{

	vec2::vec2(float x, float y) : x(x), y(y) {};

	vec2& vec2::add(const vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2& vec2::subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	vec2& vec2::divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	vec2& vec2::multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}


	vec2 operator+(const vec2& left, const vec2& right){
		return vec2(left.x + right.x, left.y + right.y);
	}
	vec2 operator-(const vec2& left, const vec2& right){
		return vec2(left.x - right.x, left.y - right.y);
	}
	vec2 operator*(const vec2& left, const vec2& right){
		return vec2(left.x * right.x, left.y * right.y);
	}
	vec2 operator/(const vec2& left, const vec2& right){
		return vec2(left.x / right.x, left.y / right.y);
	}


	vec2& vec2::operator+=(const vec2& right){
		return add(right);
	}
	vec2& vec2::operator-=(const vec2& right){
		return subtract(right);
	}
	vec2& vec2::operator*=(const vec2& right){
		return multiply(right);
	}
	vec2& vec2::operator/=(const vec2& right){
		return divide(right);
	}


	bool operator==(const vec2& left, const vec2& right){
		return left.x == right.x && left.y == right.y;
	}
	std::ostream& operator<<(std::ostream& left, const vec2& right){
		return left << "(" << right.x << ", " << right.y << ")";
	}
}
