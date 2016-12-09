#pragma once

#include "collisionresult.h"

namespace ftec {

	//Forward declare all the way !
	template <typename T>
	struct Vector2;
	template <typename T>
	struct Vector3;
	template <typename T>
	struct Vector4;
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
	T distance(const Vector2<T> &a, const Vector2<T> &b)
	{
		return (b - a).magnitude();
	}
	
	template<typename T>
	T distance(const Vector3<T> &a, const Vector3<T> &b)
	{
		return (b - a).magnitude();
	}
	
	template<typename T>
	T distance(const Vector4<T> &a, const Vector4<T> &b)
	{
		return (b - a).magnitude();
	}

	template<typename T>
	collisionresult<Vector2<T>>	intersect(const line2<T> &l1, const line2<T> &l2)
	{
		//p + t r = q + u s

		//p = origin1
		//q = origin2
		//r = dir1
		//s = dir2

		T d = Vector2<T>::cross(l1.direction(), l2.direction());

		if (d == 0)
			return false;

		return l1.origin() + l1.direction() * (
			Vector2<T>::cross(l2.origin() - l1.origin(), l2.direction()) / d );
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
	collisionresult<Vector3<T>>	intersect(const plane<T> &plane, const line3<T> &line) 
	{
		Vector3<T> lineDir = line.direction();

		T directionalDot = Vector3<T>::dot(lineDir, plane.direction);

		if (directionalDot == 0)
			return false;

		T planerDot = -(Vector3<T>::dot(plane.direction, line.a) + plane.offset);

		T result = planerDot / directionalDot;

		return line.a + lineDir * result;
	}

	template<typename T>
	collisionresult<line3<T>>	intersect(const plane<T> &p, const plane<T> &other)
	{
		Vector3<T> dir = Vector3<T>::cross(other.direction, p.direction);

		if (dir.sqrmagnitude() == 0)
			return false;

		//Perform a line intersection with the other plane
		line3<T> line(p.origin(), p.origin() + Vector3<T>::cross(dir, p.direction));

		//TODO check if this is needed.
		Vector3<T> o = intersect(other, line).result;

		return line3<T>(o, o + dir);
	}

	template<typename T>
	bool contains(const circle<T> &c, const Vector2<T> &point) {
		return distance(c.center, point) <= c.radius;
	}
	
	template<typename T>
	bool contains(const sphere<T> &c, const Vector3<T> &point) {
		return distance(c.center, point) <= c.radius;
	}

}