#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "Curve.h"

namespace ftec {

	template <typename T>
	T tween(T a, T b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	vec2<T> tween(vec2<T> a, vec2<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	vec3<T> tween(vec3<T> a, vec3<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template <typename T>
	vec4<T> tween(vec4<T> a, vec4<T> b, T f, const curves::Base &curve = curves::Linear())
	{
		return a + (b - a) * curve.interpolate(f);
	}

	template<typename T>
	inline T clamp(const T &min, const T &max, T value)
	{//Test the clamp
		if (value < min) 
			return min;
		if (value > max)
			return max;
		return value;
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
		return max(a,b) - min(a,b);
	}

	template<typename T>
	inline T abs(const T &a)
	{
		if (a < 0)
			return -a;
		return a;
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