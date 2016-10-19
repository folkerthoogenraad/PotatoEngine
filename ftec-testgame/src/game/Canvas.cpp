#include "Canvas.h"
#include "graphics/Graphics2D.h"
#include "engine/Time.h"
#include "engine/Input.h"
#include "math/StairArc.h"

#include "math/StairAlgorithm.h"

namespace ftec {

	static StairAlgorithm alg;
	static float d = 64;
	static float z = 0;

	void drawStairArc(Graphics2D &graphics, StairArc &arc)
	{
		graphics.drawArc(
			arc.getOrigin(),
			arc.getRadius(),
			false,
			arc.getStartAngle(),
			arc.getAngle() * arc.getSide()
		);
	}

	void drawStairAlgorithm(Graphics2D &graphics, StairAlgorithm &alg)
	{
		for (int i = 1; i < alg.m_Vertices.size(); ++i) {
			vec2f previousEnd = alg.m_Vertices[i - 1].m_Position;

			if (!alg.isFirst(i - 1)) {
				previousEnd = alg.getArc(i - 1).getArcEnd();
			}
			if (!alg.isLast(i)) {
				StairArc arc = alg.getArc(i);
				graphics.drawLine(previousEnd, arc.getArcStart());
				drawStairArc(graphics, arc);
			}
			else {
				graphics.drawLine(previousEnd, alg.m_Vertices[i].m_Position);
			}

		}
	}

	void Canvas::update()
	{
		auto getClosestIndex = [&]() -> int{
			int closest = 0;
			float distance = (alg.m_Vertices.front().m_Position - Input::getMousePosition()).magnitude();

			for (int i = 1; i < alg.m_Vertices.size(); i++) {
				float d = (alg.m_Vertices[i].m_Position - Input::getMousePosition()).magnitude();
				if (d < distance) {
					closest = i;
					distance = d;
				}
			}
			return closest;
		};
		if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			StairVertex vert {
				Input::getMousePosition(),
				d
			};
			alg.m_Vertices.push_back(vert);
			
		}

		if (alg.m_Vertices.size() > 0 && Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_3)) {
			alg.m_Vertices[getClosestIndex()].m_Position = Input::getMousePosition();
		}

		if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_2)) {
			alg.m_Vertices.clear();
		}

		if (Input::getScroll().y != 0 && alg.m_Vertices.size() > 0) {
			alg.m_Vertices[getClosestIndex()].m_Range += Input::getScroll().y * 5;
		}

		z = Time::sinTime / 2 + 0.5f;
	}

	void Canvas::drawSelf(Graphics2D & graphics)
	{
		potato::Bounds bounds = getGlobalBounds();

		graphics.setColor(color32::black());
		graphics.setLineWidth(4);

		drawStairAlgorithm(graphics, alg);

		graphics.setColor(color32::dkgray());
		for (auto &v : alg.m_Vertices) {
			graphics.drawCircle(v.m_Position, 8, false);
		}

		graphics.setColor(color32::green());
		vec2f r = alg.getPosition(z * alg.getLength());
		graphics.drawRectangle(rect2f(
			r.x - 8, r.y - 8,
			16, 16
		), true);
	}

}
