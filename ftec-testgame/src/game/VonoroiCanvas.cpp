#include "VonoroiCanvas.h"

#include "math/Vonoroi.h"
#include "engine/Input.h"

namespace ftec {

	static Vonoroi von({});
	static void recreate()
	{
		std::vector<vec2f> points;
		for (int i = 0; i < 500; i++) {
			points.push_back(vec2f(
				100 + rand() % 400,
				100 + rand() % 300
			));
		}

		von = Vonoroi(std::move(points));
	}


	VonoroiCanvas::VonoroiCanvas()
	{
		recreate();
	}

	void VonoroiCanvas::update()
	{
		if (Input::isKeyPressed(GLFW_KEY_SPACE)) {
			recreate();
		}
	}

	void VonoroiCanvas::drawSelf(Graphics2D & graphics)
	{
		graphics.setColor(color32(144, 140, 90, 255));
		graphics.setLineWidth(1);

		for (int i = 0; i < von.getPointCount() - 1; i++) {

			graphics.drawLine(von.getPoint(i), von.getPoint(i + 1));
		}

		graphics.setColor(color32(97, 99, 60, 255));
		for (int i = 0; i < von.getPointCount(); i++) {

			graphics.drawRectangle(rect2f(
				von.getPoint(i).x - 6, von.getPoint(i).y - 6,
				12, 12
			), true);
		}
	}
}
