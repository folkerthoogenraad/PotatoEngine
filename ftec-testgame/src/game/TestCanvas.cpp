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
		graphics.drawPrimitiveSetTexture(nullptr);
		graphics.drawPrimitiveBegin(Primitive::TRIANGLES);

		graphics.drawPrimitiveEnd();
	}

}