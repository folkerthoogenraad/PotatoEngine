#include "SoftwareGraphics.h"

#include "math/math.h"

namespace ftec {


	void SoftwareGraphics::drawLine(Paint & paint, int x, int y, int width, int height)
	{
		drawLine(paint, Vector2i(x, y), Vector2i(width, height));
	}

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
		if (point.x < 0 || point.y < 0 || point.x >= m_Image->getWidth() || point.y >= m_Image->getHeight())
			return;

		m_Image->setColor(point.x, point.y, paint.color);
	}

	void SoftwareGraphics::drawRectangle(Paint & paint, Vector2i start, Vector2i size)
	{
		if (paint.mode == Paint::FILL) {
			for (int y = 0; y < size.height; y++) {
				for (int x = 0; x < size.width; x++) {
					drawPixel(paint, start + Vector2i(x, y));
				}
			}
		}
		else {
			for (int i = 0; i < size.width; i++) {
				drawPixel(paint, start + Vector2i(i, 0));
				drawPixel(paint, start + Vector2i(i, size.height - 1));
			}
			for (int i = 0; i < size.height; i++) {
				drawPixel(paint, start + Vector2i(0, i));
				drawPixel(paint, start + Vector2i(size.width - 1, i));
			}
		}
	}

	void SoftwareGraphics::drawRectangle(Paint & paint, Rectanglei rectangle)
	{
		drawRectangle(paint, rectangle.position, rectangle.size);
	}

	void SoftwareGraphics::drawRectangle(Paint & paint, int x, int y, int width, int height)
	{
		drawRectangle(paint, Vector2i(x, y), Vector2i(width, height));
	}

}
