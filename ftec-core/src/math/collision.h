#pragma once

#include "math.h"
#include "circle.h"
#include "line.h"

namespace ftec {

	template<typename T>
	T distance(const vec2<T> &a, const vec2<T> &b)
	{
		return (b - a).magnitude();
	}

	template<typename T>
	vec2<T> intersection(const line<T> &l1, const line<T> &l2)
		{
			//p + t r = q + u s

			//p = origin1
			//q = origin2
			//r = dir1
			//s = dir2

			return l1.origin + l1.direction * (
				vec2<T>::cross(l2.origin - l1.origin, l2.direction) /
				vec2<T>::cross(l1.direction, l2.direction)
				);
		}
	
	template<typename T>
	bool intersects(const line<T> &l1, const line<T> &l2)
	{
		return vec2<T>::cross(l1.direction, l2.direction) != 0;
	}

	template<typename T>
	bool intersects(const circle<T> &c, const circle<T> &other) {
		return distance(c.center, other.center) <= c.radius + other.radius;
	}

	template<typename T>
	bool contains(const circle<T> &c, const vec2<T> &point) {
		return distance(c.center, point) < c.radius;
	}

}