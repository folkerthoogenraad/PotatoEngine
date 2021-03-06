#pragma once

#include <iostream>

#define LOG(message) std::cout << message << std::endl
#define LOG_WARNING(message) std::cout << "Warning: " << message << std::endl

#define LOG_ERROR(message) std::cerr << "(" << __FILE__ << ":" << __LINE__ << ")" << message << std::endl

#define LOG_DEBUG(message) std::cout << "(" << __FILE__ << ":" << __LINE__ << ")" << message << std::endl

#define TERMINATE(message) std::cerr << "SYSTEM ERROR:" << std::endl << message << std::endl << "Press any key to continue..."; std::cin.get(); exit(-1)
#define WAIT() std::cout << "Press any key to continue... "; std::cin.get()

namespace ftec {

	//-------------------------------------------------------------------
	// Vectors
	//-------------------------------------------------------------------
	template <typename T>
	struct Vector2;
	template <typename T>
	struct Vector3;
	template <typename T>
	struct Vector4;

	template <typename T>
	struct Quaternion;
	
	template <typename T>
	std::ostream& operator<<(std::ostream& left, const Vector2<T>& right)
	{
		return left << "(" << right.x << ", " << right.y << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream& left, const Vector3<T>& right)
	{
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream& left, const Vector4<T>& right)
	{
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ", " << right.w << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream& left, const Quaternion<T>& right)
	{
		return left << "(" << right.x << ", " << right.y << ", " << right.z << ", " << right.w << ")";
	}


	//-------------------------------------------------------------------
	// Shapes
	//-------------------------------------------------------------------

	template <typename T>
	struct Rectangle;
	template <typename T>
	struct Plane;
	template <typename T>
	struct Tetrahedron;
	template <typename T>
	struct Triangle2;
	template <typename T>
	struct Triangle3;

	template <typename T>
	std::ostream& operator<<(std::ostream &out, const Rectangle<T> &r)
	{
		return out << "(" << r.x() << ", " << r.y() << ", " << r.width() << ", " << r.height() << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream &out, const Plane<T> &r)
	{
		return out << r.direction << " * " << r.offset;
	}
	template <typename T>
	std::ostream& operator<<(std::ostream &out, const Tetrahedron<T> &r)
	{
		return out << "(" << r.a << ", " << r.b << ", " << r.c << ", " << r.d << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream &out, const Triangle2<T> &r)
	{
		return out << "(" << r.a << ", " << r.b << ", " << r.c << ")";
	}
	template <typename T>
	std::ostream& operator<<(std::ostream &out, const Triangle3<T> &r)
	{
		return out << "(" << r.a << ", " << r.b << ", " << r.c << ")";
	}

	//-------------------------------------------------------------------
	// Matrices
	//-------------------------------------------------------------------

	template <typename T>
	struct Matrix4;
	template <typename T>
	struct Matrix3;

	template <typename T>
	std::ostream& operator<<(std::ostream& left, const Matrix4<T>& right)
	{
		for (int row = 0; row < 4; ++row) {
			left << "[";
			for (int column = 0; column < 4; ++column) {
				left << right.elements[column + row * 4];
				if (column != 3)
					left << ", ";
			}
			left << "]" << std::endl;
		}

		return left;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream & left, const Matrix3<T> & right)
	{
		for (int row = 0; row < 3; ++row) {
			left << "[";
			for (int column = 0; column < 3; ++column) {
				left << right.el(column, row);// [column + row * 3];
				if (column != 2)
					left << ", ";
			}
			left << "]" << std::endl;
		}

		return left;
	}

	template <typename T>
	class Rational;

	template <typename T>
	std::ostream& operator<<(std::ostream & left, const Rational<T> & right)
	{
		if (right.getDenominator() == 1)
			return left << right.getNumerator();
		return left << "(" << right.getNumerator() << " / " << right.getDenominator() << ")";
	}
}