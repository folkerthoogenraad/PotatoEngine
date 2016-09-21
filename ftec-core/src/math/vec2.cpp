#include "math/vec2.h"

namespace ftec{

	template<typename T>
	vec2<T>::vec2(T x, T y)
	{
	}

	template<typename T>
	vec2<T>& vec2<T>::add(const vec2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	template<typename T>
	vec2<T>& vec2<T>::subtract(const vec2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template<typename T>
	vec2<T>& vec2<T>::divide(const vec2<T>& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	template<typename T>
	vec2<T>& vec2<T>::multiply(const vec2<T>& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}


	template<typename T>
	vec2<T> operator+(const vec2<T>& left, const vec2<T>& right){
		return vec2(left.x + right.x, left.y + right.y);
	}

	template<typename T>
	vec2<T> operator-(const vec2<T>& left, const vec2<T>& right){
		return vec2(left.x - right.x, left.y - right.y);
	}

	template<typename T>
	vec2<T> operator*(const vec2<T>& left, const vec2<T>& right){
		return vec2(left.x * right.x, left.y * right.y);
	}

	template<typename T>
	vec2<T> operator/(const vec2<T>& left, const vec2<T>& right){
		return vec2(left.x / right.x, left.y / right.y);
	}


	template<typename T>
	vec2<T>& vec2<T>::operator+=(const vec2<T>& right){
		return add(right);
	}
	template<typename T>
	vec2<T>& vec2<T>::operator-=(const vec2<T>& right){
		return subtract(right);
	}
	template<typename T>
	vec2<T>& vec2<T>::operator*=(const vec2<T>& right){
		return multiply(right);
	}
	template<typename T>
	vec2<T>& vec2<T>::operator/=(const vec2<T>& right){
		return divide(right);
	}


	template<typename T>
	bool operator==(const vec2<T>& left, const vec2<T>& right){
		return left.x == right.x && left.y == right.y;
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& left, const vec2<T>& right){
		return left << "(" << right.x << ", " << right.y << ")";
	}
}
