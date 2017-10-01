#pragma once

namespace ftec {

	// All have to be devisable by 12 :)
	enum class Primitive {
		LINES,			// Divisable by 2
		QUADS,			// Divisable by 4
		TRIANGLES,		// Divisable by 3
		POINTS			// Divisable by 1
	};
}