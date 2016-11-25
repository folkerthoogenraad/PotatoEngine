#pragma once

#include "collisionresult.h"

namespace ftec {

	//Forward declare all the way !
	template <typename T>
	struct vec2;
	template <typename T>
	struct vec3;
	template <typename T>
	struct vec4;
	template <typename T>
	struct circle;
	template <typename T>
	struct sphere;
	template <typename T>
	struct line2;
	template <typename T>
	struct line3;
	template <typename T>
	struct plane;

	template<typename T>
	T distance(const vec2<T> &a, const vec2<T> &b)
	{
		return (b - a).magnitude();
	}
	
	template<typename T>
	T distance(const vec3<T> &a, const vec3<T> &b)
	{
		return (b - a).magnitude();
	}
	
	template<typename T>
	T distance(const vec4<T> &a, const vec4<T> &b)
	{
		return (b - a).magnitude();
	}

	template<typename T>
	collisionresult<vec2<T>>	intersect(const line2<T> &l1, const line2<T> &l2)
	{
		//p + t r = q + u s

		//p = origin1
		//q = origin2
		//r = dir1
		//s = dir2

		T d = vec2<T>::cross(l1.direction(), l2.direction());

		if (d == 0)
			return false;

		return l1.origin() + l1.direction() * (
			vec2<T>::cross(l2.origin() - l1.origin(), l2.direction()) / d );
	}

	template<typename T>
	collisionresult<T>			intersect(const circle<T> &c, const circle<T> &other) {
		T t = (c.radius + other.radius) - distance(c.center, other.center);
		
		return collisionresult<T>(t, t >= 0);
	}

	template<typename T>
	collisionresult<T>			intersect(const sphere<T> &c, const sphere<T> &other) {
		T t = (c.radius + other.radius) - distance(c.center, other.center);

		return collisionresult<T>(t, t >= 0);
	}
	
	template<typename T>
	collisionresult<vec3<T>>	intersect(const plane<T> &plane, const line3<T> &line) 
	{
		vec3<T> lineDir = line.direction();

		T directionalDot = vec3<T>::dot(lineDir, plane.direction);

		if (directionalDot == 0)
			return false;

		T planerDot = -(vec3<T>::dot(plane.direction, line.a) + plane.offset);

		T result = planerDot / directionalDot;

		return line.a + lineDir * result;
	}

	template<typename T>
	collisionresult<line3<T>>	intersect(const plane<T> &p, const plane<T> &other)
	{
		vec3<T> dir = vec3<T>::cross(other.direction, p.direction);

		if (dir.sqrmagnitude() == 0)
			return false;

		//Perform a line intersection with the other plane
		line3<T> line(p.origin(), p.origin() + vec3<T>::cross(dir, p.direction));

		//TODO check if this is needed.
		vec3<T> o = intersect(other, line).result;

		return line3<T>(o, o + dir);
	}

	template<typename T>
	bool contains(const circle<T> &c, const vec2<T> &point) {
		return distance(c.center, point) <= c.radius;
	}
	
	template<typename T>
	bool contains(const sphere<T> &c, const vec3<T> &point) {
		return distance(c.center, point) <= c.radius;
	}

}