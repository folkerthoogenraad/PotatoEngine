#pragma once

#include <string>
#include "math/Vector2.h"
#include "Image.h"

#include "util/optional.h"

namespace ftec {
#if 0
	std::optional<Image>	loadImage(const std::string &filename);
#endif
	bool					saveImage(const Image &image, const std::string &filename);
	Vector2i glLoadImage(std::string name, unsigned int target);
}