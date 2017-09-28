#include "Slider.h"

#include "engine/Input.h"
#include "engine/Keycodes.h"

#include "graphics/Graphics2D.h"

#include "logger/log.h"

#include "math/math.h"


namespace potato {

	static const float SLIDER_BLOCK_SIZE = 16;

	Slider::Slider()
	{
		m_Focusable = true;
	}

	void Slider::drawSelf(ftec::Graphics2D & graphics)
	{
		Bounds bounds = getGlobalBounds();
		Panel::drawSelf(graphics);

		graphics.setColor(PotatoColor::lightPrimary);
		graphics.drawLine(bounds.centerLeft(), bounds.centerRight());

		graphics.setColor(PotatoColor::primary);
		graphics.drawRectangle(getSliderBounds(), true);

		if (isFocused()) {
			graphics.setColor(PotatoColor::darkPrimary);
			graphics.drawRectangle(bounds, false);
		}
	}

	void Slider::onMousePressed(Event & event)
	{
		ftec::Rectanglef blockBounds = getSliderBounds();

		if (blockBounds.contains(ftec::Input::getMousePosition())) {
			m_SliderHold = true;
			event.consume();//Event is now consumed (Idk whether or not we need this, but whatever)
		}
	}

	void Slider::onMouseReleased(Event & event)
	{
		m_SliderHold = false;
	}

	void Slider::onDrag(Event & event)
	{
		if (!m_SliderHold)
			return;

		Bounds bounds = getGlobalBounds();
		ftec::Rectanglef blockBounds = getSliderBounds();

		const float hs = SLIDER_BLOCK_SIZE / 2;
		m_Value = ftec::invLerp((float)bounds.left() + hs, (float)bounds.right() - hs, ftec::Input::getMousePosition().x);
		m_Value = ftec::clamp(0.f, 1.f, m_Value);

		if (m_Steps > 1) {
			int s = m_Steps - 1;
			m_Value = ftec::round(m_Value * s) / s;
		}

		event.consume();
	}

	Size Slider::getPreferredSize()
	{
		//TODO change these accoringly
		return Size(128,32);
	}

	ftec::Rectanglef Slider::getSliderBounds()
	{
		const float s = SLIDER_BLOCK_SIZE;
		const float hs = SLIDER_BLOCK_SIZE / 2;
		Bounds bounds = getGlobalBounds();

		ftec::Vector2f center = bounds.center();
		ftec::Vector2f position = ftec::Vector2f(ftec::lerp((float)bounds.left() + hs, (float)bounds.right() - hs, m_Value), center.y);

		return ftec::Rectanglef(position.x - hs, position.y - hs, s, s);
	}
}
