#pragma once

#define PI 3.141592654f

#include <vector>
#include <algorithm>

namespace ftec {

	template <typename T>
	struct vec2;
	template <typename T>
	struct vec3;
	template <typename T>
	struct vec4;

	template<typename T>
	inline T clamp(const T &min, const T &max, T value)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}

	template<typename T>
	inline bool inrange(const T &min, const T &max, const T &value)
	{
		return value > min && value < max;
	}

	template<typename T>
	inline const T & max(const T &a, const T &b)
	{
		if (a > b)
			return a;
		return b;
	}

	template<typename T>
	inline const T & min(const T &a, const T &b)
	{
		if (a < b)
			return a;
		return b;
	}

	template<typename T>
	inline T distance(const T &a, const T &b)
	{
		return max(a, b) - min(a, b);
	}

	template<typename T>
	inline T abs(const T &a)
	{
		if (a < 0)
			return -a;
		return a;
	}

	template<typename T>
	inline T sign(const T &a)
	{
		if (a < 0)
			return -1;
		if (a > 0)
			return 1;
		return 0;
	}

	template <typename T>
	T lerp(T a, T b, T f)
	{
		return a + (b - a) * f;
	}

	template <typename T>
	T invLerp(T a, T b, T v)
	{
		return (v - a) / (b - a);
	}

	template <typename T>
	T round(T a)
	{
		return std::round(a);
	}
	
	template <typename T>
	T floor(T a)
	{
		return std::floor(a);
	}
	
	template <typename T>
	T ceil(T a)
	{
		return std::ceil(a);
	}

}

/*
Every mathematical sturct or class should have (if applicable)

Most arguments should be const &, unless you want to modify the result.
All functions return a reference to themselves, unless they either clone, or calculate a new result

NOTE: Every structure that has a distance calculation should have a magnitude calculation (for converting the results
into world space coordinates)

The name should be:							Examples:
<name>[dimensions]							line2, line3, plane, triangle3

Methods for matrices:
translate()
translated()
scale()
scaled()
rotate()
rotated()
clone()

Methods for shapes:
transform(mat[dim] )						Transforms the shape giving the matrix
transformed(mat[dim] )						Copies and transforms the shape giving the matrix
clone()										Clones the object

Methods when applicable:
circumcenter()								Calculates and returns the circumcenter
circumcircle()								Calculates and returns the circumcircle
circumsphere()								Calculates and returns the circumsphere

boundingsphere()
boundingcircle()

normalize()
normalized()
flip()
flipped()

magnitude()
length()

distance(vec[dim])							Calculates the distance to the given point (in local coordinates)
project(vec[dim])							Projects point onto plane (and returns the direction)

center()

*/