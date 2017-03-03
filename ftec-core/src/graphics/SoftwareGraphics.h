#pragma once

#include "Image.h"

#include "math/Vector2.h"
#include "math/Vector4.h"

#include "util/not_null.h"

namespace ftec {

	//Just a placeholder ofcourse
	struct Paint {
		enum Mode {
			STROKE,
			FILL
		} mode;

		Color32 color;
	};

	class SoftwareGraphics {
	private:
		std::not_null<Image> m_Image;
	public:
		SoftwareGraphics(std::not_null<Image> image) : m_Image(image) {};

		void drawLine(Paint &paint, Vector2i start, Vector2i end);
		void drawPixel(Paint &paint, Vector2i point);
	};

}