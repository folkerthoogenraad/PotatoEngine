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
	struct Circle;
	template <typename T>
	struct Sphere;
	template <typename T>
	struct Line2;
	template <typename T>
	struct Line3;
	template <typename T>
	struct Plane;
	template <typename T>
	struct Ray3;

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
	CollisionResult<Vector2<T>>	intersect(const Line2<T> &l1, const Line2<T> &l2)
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
	CollisionResult<T>			intersect(const Circle<T> &c, const Circle<T> &other) {
		T t = (c.radius + other.radius) - distance(c.center, other.center);
		
		return CollisionResult<T>(t, t >= 0);
	}

	template<typename T>
	CollisionResult<T>			intersect(const Sphere<T> &c, const Sphere<T> &other) {
		T t = (c.radius + other.radius) - distance(c.center, other.center);

		return CollisionResult<T>(t, t >= 0);
	}
	
	template<typename T>
	CollisionResult<Vector3<T>>	intersect(const Plane<T> &plane, const Line3<T> &line) 
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
	CollisionResult<Ray3<T>>	intersectRay(const Plane<T> &p, const Plane<T> &other)
	{
		const Vector3<T> normal = Vector3<T>::cross(p.direction, other.direction);
		const T det = normal.sqrmagnitude();

		if (det == 0)
			return false;

		Ray3<T> ray;

		ray.origin = (
			(Vector3<T>::cross(normal, other.direction) * p.offset) +
			(Vector3<T>::cross(p.direction, normal) * other.offset)
			) / det;
		ray.direction = normal;

		return ray;
	}

	template<typename T>
	CollisionResult<Line3<T>>	intersect(const Plane<T> &p, const Plane<T> &other)
	{
		Vector3<T> dir = Vector3<T>::cross(other.direction, p.direction);

		if (dir.sqrmagnitude() == 0)
			return false;

		//Perform a line intersection with the other plane
		Line3<T> line(p.origin(), p.origin() + Vector3<T>::cross(dir, p.direction));

		//TODO check if this is needed.
		Vector3<T> o = intersect(other, line).result;

		return Line3<T>(o, o + dir);
	}

	template<typename T>
	bool contains(const Circle<T> &c, const Vector2<T> &point) {
		return distance(c.center, point) <= c.radius;
	}
	
	template<typename T>
	bool contains(const Sphere<T> &c, const Vector3<T> &point) {
		return distance(c.center, point) <= c.radius;
	}

}