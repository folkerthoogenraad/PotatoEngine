#include "StairArcCanvas.h"

#include "graphics/Graphics2D.h"
#include "engine/Time.h"
#include "engine/Input.h"
#include "math/StairArc.h"

#include "math/StairAlgorithm.h"
#include "math/math.h"

#include "engine/Keycodes.h"

#include <sstream>

namespace ftec {

	//Yea, who cares anyway
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
			graphics.setColor(Color32::black());

			Vector2f previousEnd = alg.m_Vertices[i - 1].m_Position;

			if (!alg.isFirst(i - 1)) {
				previousEnd = alg.getArc(i - 1).getArcEnd();
			}
			if (!alg.isLast(i)) {
				StairArc arc = alg.getArc(i);
				graphics.drawLine(previousEnd, arc.getArcStart());
				drawStairArc(graphics, arc);

				if (Input::isKeyDown(KEY_SPACE)) {
					graphics.setColor(Color32::blue());
					graphics.drawRectangle(Rectanglef(
						arc.getArcStart().x - 4,
						arc.getArcStart().y - 4, 8, 8
					), true);
					graphics.drawRectangle(Rectanglef(
						arc.getArcEnd().x - 4,
						arc.getArcEnd().y - 4, 8, 8
					), true);
					graphics.setColor(Color32::green());
					graphics.drawRectangle(Rectanglef(
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

	StairArcCanvas::StairArcCanvas()
	{
		m_Focusable = true;
	}

	void StairArcCanvas::update()
	{
		if (!isFocused())
			return;
		auto getClosestIndex = [&]() -> int {
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
		if (Input::isMouseButtonPressed(MOUSE_BUTTON_1)) {
			StairVertex vert{
				Input::getMousePosition(),
				d
			};
			alg.m_Vertices.push_back(vert);

		}

		if (alg.m_Vertices.size() > 0 && Input::isMouseButtonDown(MOUSE_BUTTON_3)) {
			alg.m_Vertices[getClosestIndex()].m_Position = Input::getMousePosition();
		}

		if (Input::isMouseButtonReleased(MOUSE_BUTTON_2)) {
			alg.m_Vertices.clear();
		}

		if (Input::isKeyPressed(KEY_ENTER)) {
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

	void StairArcCanvas::drawSelf(Graphics2D & graphics)
	{
		potato::Bounds bounds = getGlobalBounds();

		graphics.setColor(Color32::black());
		graphics.drawString("Left mouse to add points\nMiddle mouse to move point\nRight mouse to clear curve\nSpace to show handles\nScroll to increase distance for hovering point\nPress enter to auto calculate distances", bounds.topleft() + Vector2i(2, 2));

		std::stringstream ss;
		ss << "Point count: " << alg.m_Vertices.size();
		graphics.drawString(ss.str(), bounds.topleft() + Vector2i(256, 2));

		graphics.setColor(Color32::black());
		graphics.setLineWidth(6);

		drawStairAlgorithm(graphics, alg);

		graphics.setColor(Color32(97, 99, 60, 255));
		for (auto &v : alg.m_Vertices) {
			graphics.drawRectangle(Rectanglef(
				v.m_Position.x - 6, v.m_Position.y - 6,
				12, 12
			), true);
		}

		/*
		graphics.setColor(Color32::green());
		Vector2f r = alg.getPosition(z * alg.getLength());
		graphics.drawRectangle(Rectanglef(
		r.x - 8, r.y - 8,
		16, 16
		), true);*/
	}

}