#include "hash.h"

namespace ftec {

	HashType hash(char const * input)
	{
		return *input ?
			static_cast<unsigned int>(*input) + 33 * hash(input + 1) :
			5381;

	}

	HashType hash(const std::string & str)
	{
		return hash(str.c_str());
	}

}
