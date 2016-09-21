#include "math/vec4.h"

namespace ftec{

	template<typename T>
	vec4<T>::vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

	template<typename T>
	vec4<T>&  vec4<T>::add(const vec4<T>&  other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	template<typename T>
	vec4<T>&  vec4<T>::subtract(const vec4<T>&  other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	template<typename T>
	vec4<T>&  vec4<T>::divide(const vec4<T>&  other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	template<typename T>
	vec4<T>&  vec4<T>::multiply(const vec4<T>&  other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}


	template<typename T>
	vec4<T> operator+(const vec4<T>&  left, const vec4<T>&  right){
		return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}
	template<typename T>
	vec4<T> operator-(const vec4<T>&  left, const vec4<T>&  right){
		return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}
	template<typename T>
	vec4<T> operator*(const vec4<T>&  left, const vec4<T>&  right){
		return vec4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}
	template<typename T>
	vec4<T> operator/(const vec4<T>&  left, const vec4<T>&  right){
		return vec4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
	}


	template<typename T>
	vec4<T>&  vec4<T>::operator+=(const vec4<T>&  right){
		return add(right);
	}
	template<typename T>
	vec4<T>&  vec4<T>::operator-=(const vec4<T>&  right){
		return subtract(right);
	}
	template<typename T>
	vec4<T>&  vec4<T>::operator*=(const vec4<T>&  right){
		return multiply(right);
	}
	template<typename T>
	vec4<T>&  vec4<T>::operator/=(const vec4<T>&  right){
		return divide(right);
	}


	template<typename T>
	bool operator==(const vec4<T>&  left, const vec4<T>&  right){
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& left, const vec4<T>&  right){
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ", " << right.w << ")";
	}
}
