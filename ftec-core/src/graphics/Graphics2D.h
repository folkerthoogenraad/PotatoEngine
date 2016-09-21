#pragma once
#include "math/rect.h"

namespace ftec {
	class Graphics2D {
	protected:
		rect2i m_ClippingRectangle;
	public:
		//Set the clipping rectangle
		void clip(const rect2i &rectangle);
		void flush();
		void clear();

		//Getters

		//Returns the current clipping area, as set by clip
		inline const rect2i &getClip() { return m_ClippingRectangle; };
	};
}