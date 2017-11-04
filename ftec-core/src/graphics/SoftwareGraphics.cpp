#include "SoftwareGraphics.h"

#include "math/math.h"

namespace ftec {

	void SoftwareGraphics::drawLine(Paint & paint, Vector2i start, Vector2i end)
	{
		Vector2i delta = end - start;

		//X axis line
		if (abs(delta.x) > abs(delta.y)) {
			float y = 0.0f;
			float dy = (float)delta.y / (float) abs(delta.x);

			int dx = sign(delta.x);
			
			for (int x = 0; x != delta.x; x += dx) {
				drawPixel(paint, Vector2i(start.x + x, start.y + (int) floor(y)));
				y += dy;
			}
		}

		//Y axis line
		else {
			float x = 0.0f;
			float dx = (float)delta.x / (float)abs(delta.y);

			int dy = sign(delta.y);

			for (int y = 0; y != delta.y; y += dy){
				drawPixel(paint, Vector2i(start.x + (int) floor(x), start.y + y));
				x += dx;
			}
		}
	}

	void SoftwareGraphics::drawPixel(Paint & paint, Vector2i point)
	{
		m_Image->setColor(point.x, point.y, paint.color);
	}

}
