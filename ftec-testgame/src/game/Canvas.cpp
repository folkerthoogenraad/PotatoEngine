#include "Canvas.h"
#include "graphics/Graphics2D.h"
#include "engine/Time.h"
#include "engine/Input.h"
#include "math/StairArc.h"

#include "math/StairAlgorithm.h"

#include <sstream>

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
			arc.getAngle()// *arc.getSide()
		);
	}

	void drawStairAlgorithm(Graphics2D &graphics, StairAlgorithm &alg)
	{
		for (int i = 1; i < alg.m_Vertices.size(); ++i) {
			graphics.setColor(color32::black());

			vec2f previousEnd = alg.m_Vertices[i - 1].m_Position;

			if (!alg.isFirst(i - 1)) {
				previousEnd = alg.getArc(i - 1).getArcEnd();
			}
			if (!alg.isLast(i)) {
				StairArc arc = alg.getArc(i);
				graphics.drawLine(previousEnd, arc.getArcStart());
				drawStairArc(graphics, arc);

				if (Input::isKeyDown(GLFW_KEY_SPACE)) {
					graphics.setColor(color32::blue());
					graphics.drawRectangle(rect2f(
						arc.getArcStart().x - 4,
						arc.getArcStart().y - 4, 8, 8
					), true);
					graphics.drawRectangle(rect2f(
						arc.getArcEnd().x - 4,
						arc.getArcEnd().y - 4, 8, 8
					), true);
					graphics.setColor(color32::green());
					graphics.drawRectangle(rect2f(
						arc.getOrigin().x - 4,
						arc.getOrigin().y - 4, 8, 8
					), true);
				}
			}
			else {
				graphics.drawLine(previousEnd, alg.m_Vertices[i].m_Position);
			}

		}
	}

	Canvas::Canvas()
	{
		m_Focusable = true;
	}

	void Canvas::update()
	{
		if (!m_Focus)
			return;
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
			StairVertex vert{
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

		if (Input::isKeyPressed(GLFW_KEY_ENTER)) {
			for (int i = 1; i + 1 < alg.m_Vertices.size(); ++i) {
				auto &previous = alg.m_Vertices[i - 1];
				auto &current = alg.m_Vertices[i];
				auto &next = alg.m_Vertices[i + 1];

				float pDistance = (current.m_Position - previous.m_Position).magnitude();
				float nDistance = (next.m_Position - current.m_Position).magnitude();

				if (!alg.isFirst(i - 1)) {
					pDistance /= 2;
				}
				if (!alg.isLast(i + 1)) {
					nDistance /= 2;
				}

				current.m_Range = min(pDistance, nDistance);
			}
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
		graphics.drawString("Left mouse to add points\nMiddle mouse to move point\nRight mouse to clear curve\nSpace to show handles\nScroll to increase distance for hovering point\nPress enter to auto calculate distances", bounds.topleft() + vec2i(2, 2));

		std::stringstream ss;
		ss << "Point count: " << alg.m_Vertices.size();
		graphics.drawString(ss.str(), bounds.topleft() + vec2i(256, 2));

		graphics.setColor(color32::black());
		graphics.setLineWidth(6);

		drawStairAlgorithm(graphics, alg);

		graphics.setColor(color32(97,99,60,255));
		for (auto &v : alg.m_Vertices) {
			graphics.drawRectangle(rect2f(
				v.m_Position.x - 6, v.m_Position.y - 6,
				12, 12
			), true);
		}

		/*
		graphics.setColor(color32::green());
		vec2f r = alg.getPosition(z * alg.getLength());
		graphics.drawRectangle(rect2f(
		r.x - 8, r.y - 8,
		16, 16
		), true);*/
	}

}