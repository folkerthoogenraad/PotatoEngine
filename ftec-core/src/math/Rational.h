#pragma once

#if UB
#include <boost/multiprecision/rational_adaptor.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/pool/pool.hpp>
#include <boost/pool/pool_alloc.hpp>

namespace ftec {
	typedef boost::multiprecision::number<
		boost::multiprecision::rational_adaptor<
			boost::multiprecision::cpp_int_backend<
			0,													// minBits (default 0)
			0,													// maxBits (default 0)
			boost::multiprecision::signed_magnitude,			// cpp_integer_type sign (default signed_magnitude)
			boost::multiprecision::unchecked,					// cpp_int_check_type checked (default unchecked)
			std::allocator<boost::multiprecision::limb_type>	// allocator (default std::allocator<limb_type>, where limb_type == unsigned long) 
			>
		>
	> rational; //Define it like a primitive for funz
}

#else

#include <boost/multiprecision/cpp_int.hpp>

namespace ftec {
	typedef boost::multiprecision::cpp_rational rational; //Define it like a primitive for funz
}

#endif

namespace ftec {
	template <typename T>
	struct Vector2;
	template <typename T>
	struct Vector3;
	template <typename T>
	struct Vector4;

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
	struct Matrix4;
	template <typename T>
	struct Matrix3;
	template <typename T>
	struct Matrix2;

	typedef Vector2<rational> Vector2r;
	typedef Vector3<rational> Vector3r;
	typedef Vector4<rational> Vector4r;

	typedef Rectangle<rational> Rectangler;
	typedef Plane<rational> Planer;
	typedef Tetrahedron<rational> Tetrahedronr;
	typedef Triangle2<rational> Triangle2r;
	typedef Triangle3<rational> Triangle3r;

	typedef Matrix4<rational> Matrix4r;
	typedef Matrix3<rational> Matrix3r;
	typedef Matrix2<rational> Matrix2r;
}