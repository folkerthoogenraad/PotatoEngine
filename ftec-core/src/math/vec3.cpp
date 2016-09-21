#include "math/vec3.h"

namespace ftec{

	template<typename T>
	vec3<T>::vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	template<typename T>
	vec3<T>& vec3<T>::add(const vec3<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::subtract(const vec3<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::divide(const vec3<T>& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::multiply(const vec3<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::add(T other)
	{
		x += other;
		y += other;
		z += other;
		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::subtract(T other)
	{
		x -= other;
		y -= other;
		z -= other;
		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::divide(T other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	template<typename T>
	vec3<T>& vec3<T>::multiply(T other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	template<typename T>
	vec3<T> & vec3<T>::normalize()
	{
		T l = magnitude();
		if (l > 0) {
			x /= l;
			y /= l;
			z /= l;
		}
		return *this;
	}

	template<typename T>
	T vec3<T>::magnitude()
	{
		return (T) sqrt(x*x + y*y + z*z);
	}

	template<typename T>
	vec3<T> vec3<T>::cross(const vec3<T>& left, const vec3<T>& right)
	{
		return vec3<T>(
			left.y * right.z - left.z * right.y,
			left.z * right.x - left.x * right.z,
			left.x * right.y - left.y * right.x
		);
	}

	template<typename T>
	T vec3<T>::dot(const vec3<T>& left, const vec3<T>& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	template<typename T>
	vec3<T> operator+(const vec3<T>& left, const vec3<T>& right){
		return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}
	template<typename T>
	vec3<T> operator-(const vec3<T>& left, const vec3<T>& right){
		return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}
	template<typename T>
	vec3<T> operator*(const vec3<T>& left, const vec3<T>& right){
		return vec3(left.x * right.x, left.y * right.y, left.z * right.z);
	}
	template<typename T>
	vec3<T> operator/(const vec3<T>& left, const vec3<T>& right){
		return vec3(left.x / right.x, left.y / right.y, left.z / right.z);
	}

	template<typename T>
	vec3<T> operator+(const vec3<T>& left, T right) {
		return vec3(left.x + right, left.y + right, left.z + right);
	}
	template<typename T>
	vec3<T> operator-(const vec3<T>& left, T right) {
		return vec3(left.x - right, left.y - right, left.z - right);
	}
	template<typename T>
	vec3<T> operator*(const vec3<T>& left, T right) {
		return vec3(left.x * right, left.y * right, left.z * right);
	}
	template<typename T>
	vec3<T> operator/(const vec3<T>& left, T right) {
		return vec3(left.x / right, left.y / right, left.z / right);
	}

	template<typename T>
	vec3<T>& vec3<T>::operator+=(const vec3<T>& right){
		return add(right);
	}
	template<typename T>
	vec3<T>& vec3<T>::operator-=(const vec3<T>& right){
		return subtract(right);
	}
	template<typename T>
	vec3<T>& vec3<T>::operator*=(const vec3<T>& right){
		return multiply(right);
	}
	template<typename T>
	vec3<T>& vec3<T>::operator/=(const vec3<T>& right){
		return divide(right);
	}

	template<typename T>
	vec3<T> operator-(const vec3<T>& left)
	{
		return vec3<T>(-left.x, -left.y, -left.z);
	}

	template<typename T>
	bool operator==(const vec3<T>& left, const vec3<T>& right){
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& left, const vec3<T>& right){
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ")";
	}
}
