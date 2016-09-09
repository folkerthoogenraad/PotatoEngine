#include "ioutils.h"
#include <fstream>
#include <sstream>
#include "logger/log.h"

namespace ftec {
	std::string IOUtils::fileToString(std::string filename)
	{
		std::ifstream file(filename);
		return std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	}
}
