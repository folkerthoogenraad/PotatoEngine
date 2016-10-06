#include "Slider.h"
#include "math/helpers.h"
#include "engine/Input.h"
#include "graphics/Graphics2D.h"
#include "logger/log.h"
#include "PotatoUI.h"

namespace potato {

	static const float SLIDER_BLOCK_SIZE = 16;

	Slider::Slider()
	{
		m_Focusable = true;
	}

	void Slider::drawSelf(ftec::Graphics2D & graphics)
	{
		Panel::drawSelf(graphics);

		graphics.setColor(PotatoColor::lightPrimary);
		graphics.drawLine(m_Bounds.centerLeft(), m_Bounds.centerRight());

		graphics.setColor(PotatoColor::primary);
		graphics.drawRectangle(getSliderBounds(), true);

		if (m_Focus) {
			graphics.setColor(PotatoColor::darkPrimary);
			graphics.drawRectangle(m_Bounds, false);
		}
	}

	void Slider::update()
	{
		Panel::update();

		ftec::rect2f blockBounds = getSliderBounds();

		if (ftec::Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			if (blockBounds.contains(ftec::Input::getMousePosition())) {
				m_SliderHold = true;
			}
		}
		if (ftec::Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_1)) {
			m_SliderHold = false;
		}
		if (ftec::Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_1) && m_SliderHold) {
			const float hs = SLIDER_BLOCK_SIZE / 2;
			m_Value = ftec::invLerp((float)m_Bounds.left() + hs, (float)m_Bounds.right() - hs, ftec::Input::getMousePosition().x);
			m_Value = ftec::clamp(0.f, 1.f, m_Value);

			if (m_Steps > 1) {
				int s = m_Steps - 1;
				m_Value = ftec::round(m_Value * s) / s;
			}
		}
	}

	ftec::rect2f Slider::getSliderBounds()
	{
		const float s = SLIDER_BLOCK_SIZE;
		const float hs = SLIDER_BLOCK_SIZE / 2;

		ftec::vec2f center = m_Bounds.center();
		ftec::vec2f position = ftec::vec2f(ftec::lerp((float)m_Bounds.left() + hs, (float)m_Bounds.right() - hs, m_Value), center.y);

		return ftec::rect2f(position.x - hs, position.y - hs, s, s);
	}
}
