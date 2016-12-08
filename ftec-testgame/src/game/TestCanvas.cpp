#include "TestCanvas.h"

namespace ftec {

	TestCanvas::TestCanvas()
	{

	}

	void TestCanvas::update()
	{

	}

	void TestCanvas::drawSelf(Graphics2D & graphics)
	{
		graphics.setDepth(1);
		graphics.setColor(color32::red());
		graphics.drawRectangle(rectf(2, 2, 64, 64), true);

		graphics.setDepth(-1);
		graphics.setColor(color32::blue());
		graphics.drawRectangle(rectf(16, 16, 64, 64), true);

	}

}