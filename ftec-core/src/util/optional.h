#pragma once

#include <boost/optional.hpp>

namespace std {
	//This can change whenever std::optional is a thing
	template <typename T>
	using optional = boost::optional<T>;
}