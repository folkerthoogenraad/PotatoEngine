#include "Slider.h"

#include "engine/Input.h"
#include "engine/Keycodes.h"

#include "graphics/Graphics2D.h"

#include "logger/log.h"

#include "math/math.h"


namespace potato {

	static const float SLIDER_BLOCK_WIDTH = 10;

	Slider::Slider(std::shared_ptr<ftec::EngineContext> context)
		: Panel(context)
	{
		m_Focusable = true;
	}

	void Slider::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Bounds bounds = getGlobalBounds();
		Panel::drawSelf(graphics, style);

		graphics.setLineWidth(6.0f);

		const float hs = SLIDER_BLOCK_WIDTH / 2;

		auto sliderPosition = bounds.centerLeft()
			+ ftec::Vector2f(hs, 0)
			+ ftec::Vector2f(bounds.width() - hs * 2.0f, 0) * m_Value;

		graphics.setColor(style.m_AccentColor);
		graphics.drawLine(bounds.centerLeft(), sliderPosition);

		graphics.setColor(style.m_DarkBackground);
		graphics.drawLine(sliderPosition, bounds.centerRight());

		graphics.setLineWidth(2.0f);

		graphics.setColor(style.m_DarkBackground);
		graphics.drawRectangle(Bounds::centered(sliderPosition.x, sliderPosition.y, SLIDER_BLOCK_WIDTH, bounds.height() * 0.8f), true);

		graphics.setColor(style.m_AccentColor);
		graphics.drawLine(
			sliderPosition + ftec::Vector2f(0, bounds.height() * 0.25f), 
			sliderPosition + ftec::Vector2f(0, -bounds.height() * 0.25f));
	}

	void Slider::onMousePressed(ftec::Event & event)
	{
		onDrag(event);
	}

	void Slider::onDrag(ftec::Event & event)
	{
		Bounds bounds = getGlobalBounds();

		const float hs = SLIDER_BLOCK_WIDTH / 2;
		m_Value = ftec::invLerp((float)bounds.left() + hs, (float)bounds.right() - hs, event.getMousePosition().x);
		m_Value = ftec::clamp(0.f, 1.f, m_Value);

		if (m_Steps > 1) {
			int s = m_Steps - 1;
			m_Value = ftec::round(m_Value * s) / s;
		}
		repaint();

		event.consume();
	}

	Size Slider::getPreferredSize()
	{
		//TODO change these accoringly
		return Size(128,32);
	}
}
