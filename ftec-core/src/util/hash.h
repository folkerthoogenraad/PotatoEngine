#pragma once

#include <string>

namespace ftec {

	typedef unsigned int HashType;

	HashType constexpr const_hash(char const *input) {
		return *input ?
			static_cast<unsigned int>(*input) + 33 * const_hash(input + 1) :
			5381;
	}

	HashType hash(char const *input);
	HashType hash(const std::string &str);

}