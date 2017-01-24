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