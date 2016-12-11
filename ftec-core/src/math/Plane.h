#pragma once

#include "Vector3.h"

namespace ftec {

	template <typename T>
	struct Triangle3;
	template <typename T>
	struct Line3;
	template <typename T>
	struct Plane;

	template <typename T>
	struct Plane {
		//Ax + By + Cz + D
		Vector3<T> direction;
		T offset;

		Plane() {}
		explicit Plane(const Triangle3<T> &triangle)
		{
			direction = triangle.normal();
			offset = -Vector3<T>::dot(triangle.a, direction);
		}
		Plane(const Vector3<T> position, const Vector3<T> direction) : direction(direction)
		{
			offset = -Vector3<T>::dot(position, direction);
		}
		Plane(const Vector3<T> &dir, const T &offset) : direction(dir), offset(offset) {}
		
		T distanceFrom(const Vector3<T> &p) const
		{
			T c = Vector3<T>::dot(direction, direction);
			T r = Vector3<T>::dot(direction, p);

			//ax + by + cz + d = 0
			//ax + by + cz = -d

			return (-offset - r) / c;
		}
		Plane<T> clone() const { return Plane<T>(*this); }
		
		Plane<T> &flip() 
		{
			direction = -direction;
			offset = -offset;
			return *this; 
		}
		Plane<T> flipped() const { return clone().flip(); }

		Vector3<T> origin() const  
		{
			return direction * distanceFrom(Vector3f());
		}

		Plane<T> &normalize() 
		{
			T mag = direction.magnitude();
			direction /= mag;
			offset /= mag;

			return *this;
		}
		Plane<T> normalized() const
		{
			return clone().normalize();
		}

		T magnitude() const { return direction.magnitude(); }

		Vector3<T> project(const Vector3<T> &p) const
		{
			float t = distanceFrom(p);
			return p + direction * t;
		}
	};

	typedef Plane<float> Planef;
	typedef Plane<double> Planed;
}