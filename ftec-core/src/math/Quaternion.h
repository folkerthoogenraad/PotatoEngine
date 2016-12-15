#pragma once

#include <array>
#include "math/math.h"	//For sin, cos, etc

//TODO find out if this is the right thing or not
namespace ftec {

	template<typename T> struct Vector3;
	template<typename T> struct Matrix4;

	template<typename T>
	struct Quaternion
	{
		union {
			struct {
				T x, y, z, w;
			};

			std::array<T, 4> v;
		};

		Quaternion() : Quaternion(0, 0, 0, 1) {}
		Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		Quaternion<T> &multiply(const Quaternion<T> &other)
		{
			Quaternion result;

			result.v[0] = v[3] * other.v[0] + v[0] * other.v[3] + v[1] * other.v[2] - v[2] * other.v[1];
			result.v[1] = v[3] * other.v[1] + v[1] * other.v[3] + v[2] * other.v[0] - v[0] * other.v[2];
			result.v[2] = v[3] * other.v[2] + v[2] * other.v[3] + v[0] * other.v[1] - v[1] * other.v[0];
			result.v[3] = v[3] * other.v[3] - v[0] * other.v[0] - v[1] * other.v[1] - v[2] * other.v[2];

			v = result.v;

			return *this;
		}
		Quaternion<T> multiplied(const Quaternion<T> &other) const
		{
			return clone().multiply(other);
		}

		Quaternion<T> &inverse()
		{
			x = -x;
			y = -y;
			z = -z;

			return *this;
		}
		Quaternion<T> inversed() const
		{
			return clone().inverse();
		}

		inline T magnitude() const
		{
			return (T)sqrt(sqrmagnitude());
		}
		inline T sqrmagnitude() const
		{
			return (T)x*x + y*y + z*z + w*w;
		}

		Quaternion<T> &normalize()
		{
			T m = magnitude();
			x /= m;
			y /= m;
			z /= m;
			w /= m;

			return *this;
		}
		Quaternion<T> normalized() const
		{
			return clone().normalize();
		}

		Quaternion<T> clone() const
		{
			return Quaternion(*this);
		}

		Vector3<T> euler() const
		{
			T sqrW = w*w;
			T sqrX = x*x;
			T sqrY = y*y;
			T sqrZ = z*z;
			return Vector3<T>(
				-atan2((2 * (-w*x + y*z)), (sqrW - sqrX - sqrY + sqrZ)),
				-asin(-2 * (x*z + w*y)),
				-atan2((2 * (x*y - w*z)), (sqrW + sqrX - sqrY - sqrZ))
				);
		}
		Matrix4<T> matrix() const
		{
			//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/

			Matrix4<T> out = Matrix4<T>::identity();

			out.el(0, 0) = 1 -	2 * y * y - 2 * z * z;
			out.el(1, 0) =		2 * x * y - 2 * z * w;
			out.el(2, 0) =		2 * x * z + 2 * y * w;
			
			out.el(0, 1) =		2 * x * y + 2 * z * w;
			out.el(1, 1) = 1 -	2 * x * x - 2 * z * z;
			out.el(2, 1) =		2 * y * z - 2 * x * w;


			out.el(0, 2) =		2 * x * z - 2 * y * w;
			out.el(1, 2) =		2 * y * z + 2 * x * w;
			out.el(2, 2) = 1 -	2 * x * x - 2 * y * y;

			return out.transpose();
		}

		static Quaternion<T> fromEuler(const Vector3<T> &euler)
		{
			//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
			Quaternion<T> q;

			T t0 = cos(euler.z * (T)0.5);
			T t1 = sin(euler.z * (T)0.5);
			T t2 = cos(euler.x * (T)0.5);
			T t3 = sin(euler.x * (T)0.5);
			T t4 = cos(euler.y * (T)0.5);
			T t5 = sin(euler.y * (T)0.5);

			q.w = t0 * t2 * t4 + t1 * t3 * t5;
			q.x = t0 * t3 * t4 - t1 * t2 * t5;
			q.y = t0 * t2 * t5 + t1 * t3 * t4;
			q.z = t1 * t2 * t4 - t0 * t3 * t5;

			return q;
		}
		static Quaternion<T> axisAngle(const Vector3<T> &axis, T angle)
		{
			Quaternion quat;

			quat.w = (T)cos(angle / (T)2.0);

			quat.x = axis.x * (T)sin(angle / (T)2.0);
			quat.y = axis.y * (T)sin(angle / (T)2.0);
			quat.z = axis.z * (T)sin(angle / (T)2.0);

			return quat;
		}
		static Quaternion<T> identity()
		{
			return Quaternion<T>();
		}

		Quaternion operator*(const Quaternion &right)
		{
			return multiplied(right);
		}
		Quaternion &operator*=(const Quaternion &right)
		{
			return multiply(right);
		}
	};

	typedef Quaternion<float> Quaternionf;
	typedef Quaternion<double> Quaterniond;
}