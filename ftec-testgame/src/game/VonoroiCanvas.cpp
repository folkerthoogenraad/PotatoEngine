#include "VonoroiCanvas.h"

#include "math/Delaunay.h"
#include "math/triangle.h"
#include "engine/Input.h"

namespace ftec {

	static Delaunay del = Delaunay();
	static std::vector<vec2f> points {};

	static void recreate()
	{
		if (points.size() > 0) {
			del.triangulate(points);
		}
	}


	VonoroiCanvas::VonoroiCanvas()
	{
		recreate();
	}

	void VonoroiCanvas::update()
	{
		if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {
			points.clear();
			recreate();
		}
		if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			points.push_back(Input::getMousePosition());
			recreate();
		}
	}

	void VonoroiCanvas::drawSelf(Graphics2D & graphics)
	{

		//Orange
		//graphics.setColor(color32(255, 99, 60, 255));

		//Background
		//graphics.setColor(color32(240, 240, 240, 255));

		//Green
		//graphics.setColor(color32(97, 99, 60, 255));

		//Blue
		//graphics.setColor(color32(97, 99, 255, 255));

		graphics.setColor(color32(240, 240, 240, 255));

		graphics.drawRectangle(this->getGlobalBounds(), true);


		graphics.setColor(color32(97, 99, 60, 255)); 
		graphics.setPointSize(10);
		
		for (int i = 0; i < del.getPointCount(); i++) {
			graphics.drawPoint(del.getPoint(i));
		}


		graphics.setColor(color32(144, 140, 90, 255));
		graphics.setLineWidth(1);

		LOG(del.getTriangleCount());

		for (int i = 0; i < del.getTriangleCount(); i++) {
			graphics.setColor(color32(144, 140, 90, 255));
			auto triangle = del.getTriangle(i);

			graphics.drawLine(triangle.edgeab());
			graphics.drawLine(triangle.edgebc());
			graphics.drawLine(triangle.edgeca());

			graphics.setColor(color32(97, 99, 255, 255));
			graphics.setCirclePrecision(64);
			if(Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
				graphics.drawCircle(triangle.circumcircle(), false);
		}
	}
}
