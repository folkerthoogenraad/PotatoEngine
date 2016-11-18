#include "VoronoiCanvas.h"

#include "math/Voronoi.h"
#include "math/Delaunay.h"
#include "math/triangle2.h"
#include "engine/Input.h"
#include "engine/Time.h"
#include "engine/Engine.h"

#include "math/lego2.h"


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


	VoronoiCanvas::VoronoiCanvas()
	{
		recreate();
	}

	void VoronoiCanvas::update()
	{
		if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {
			points.clear();
			recreate();
		}
		if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			points.push_back(Input::getMousePosition());
			recreate();
		}
		if (Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_3)) {
			points.back() = Input::getMousePosition();
			recreate();
		}
		if (Input::isKeyTyped(GLFW_KEY_ENTER)) {
			points.clear();
			for (int i = 0; i < 200; i++) {
				points.push_back(vec2f(
					rand() % (int)(Engine::getWindow().getWidth() - 32) + 16,
					rand() % (int)(Engine::getWindow().getHeight() - 32) + 16
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

	void VoronoiCanvas::drawSelf(Graphics2D & graphics)
	{

		//Orange
		//graphics.setColor(color32(255, 99, 60, 255));

		//Background
		//graphics.setColor(color32(240, 240, 240, 255));

		//Green
		//graphics.setColor(color32(97, 99, 60, 255));

		//Blue
		//graphics.setColor(color32(97, 99, 255, 255));

		graphics.setPointType(Graphics2D::PointType::CIRCLE);
		graphics.setPointSize(10);

		graphics.setColor(color32(240, 240, 240, 255));

		graphics.drawRectangle(this->getGlobalBounds(), true);
		

		graphics.setColor(color32(220, 220, 220, 255));
		graphics.drawRectangle(voronoi.getBoundingBox(), true);

		for (int i = 0; i < voronoi.getPointCount(); i++) {

			auto &l = voronoi.getLego(i);

			if (l.m_Vertices.size() > 1) {
				graphics.setLineWidth(2);
				graphics.setColor(color32(97, 99, 255, 255));
				for (int li = 1; li < l.m_Vertices.size(); ++li) {
					graphics.drawLine(l.m_Vertices[li - 1], l.m_Vertices[li]);
				}
				graphics.drawLine(l.m_Vertices.front(), l.m_Vertices.back());
			}

			if (!Input::isKeyDown(GLFW_KEY_Z))
				continue;

			if (Input::isKeyDown(GLFW_KEY_SPACE)) {
				graphics.setColor(color32(144, 140, 90, 255));
				graphics.setLineWidth(1);

				const auto &v = voronoi.getNeighbours(i);

				for (int j : v) {
					line2f line(
						voronoi.getPoint(i),
						voronoi.getPoint(j)
					);
					graphics.drawLine(line);
				}
			}


			graphics.setColor(color32(97, 99, 60, 255));

			//if(voronoi.isOnHull(i))
			//	graphics.setColor(color32(255, 99, 60, 255));

			graphics.drawPoint(voronoi.getPoint(i));

			for (auto v : l.m_Vertices)
			{
				graphics.setColor(color32(255, 99, 255, 255));
				graphics.drawPoint(v);
			}


		}



	}
}
