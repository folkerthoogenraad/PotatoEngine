#include "VonoroiCanvas.h"

#include "math/Voronoi.h"
#include "math/Delaunay.h"
#include "math/triangle.h"
#include "engine/Input.h"

namespace ftec {

	static Voronoi voronoi;
	static std::vector<vec2f> points {};

	static void recreate()
	{
		if (points.size() > 0) {
			Delaunay del;
			del.triangulate(points);
			voronoi.create(del);
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
		if (Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
			points.back() = Input::getMousePosition();
			recreate();
		}
		if (Input::isKeyTyped(GLFW_KEY_ENTER)) {
			points.clear();
			for (int i = 0; i < 50; i++) {
				points.push_back(vec2f(
					rand() % 512 + 256,
					rand() % 512 + 128
				));
			}
			recreate();
		}
		if (Input::isKeyTyped(GLFW_KEY_C)) {
			points.clear();
			for (int x = 0; x < 18; x++) {
				for (int y = 0; y < 10; y++) {
					points.push_back(vec2f(
						x * 64 + 64, y * 64 + 64
					));
				}
			}
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

		graphics.setColor(color32(220, 220, 220, 255));
		graphics.drawRectangle(voronoi.getBoundingBox(), true);


		graphics.setPointSize(10);
		
		for (int i = 0; i < voronoi.getPointCount(); i++) {
			graphics.setColor(color32(97, 99, 60, 255));
			graphics.drawPoint(voronoi.getPoint(i));

			graphics.setColor(color32(144, 140, 90, 255));
			graphics.setLineWidth(1);
			
			const auto &v = voronoi.getNeighbours(i);
			for (int j : v) {
				line2f line(
					voronoi.getPoint(i),
					voronoi.getPoint(j)
				);
				graphics.drawLine(line);
				//graphics.drawLine(line.normal());
			}
		}



	}
}
