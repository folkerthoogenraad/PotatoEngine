#include "Knob.h"
#include "math/math.h"
#include "logger/log.h"

namespace potato {

	static const float SENSITIVITY = -200.0f;
	static const float KNOB_LENGTH = 8.0f;
	static const float MIN_ANGLE = -PI - PI / 4;
	static const float MAX_ANGLE = PI / 4;
	
	Knob::Knob()
	{
		m_Focusable = true;
	}

	void Knob::drawSelf(ftec::Graphics2D & graphics)
	{
		Bounds b = getGlobalBounds();

		auto center = b.center();
		auto radius = ftec::min(b.width(), b.height()) / 2.0f;

		float v = m_Value;

		if(m_Steps > 1) 
			v = ftec::floor(m_Value * m_Steps) / m_Steps;

		auto angle = ftec::lerp(MIN_ANGLE, MAX_ANGLE, v);
	
		graphics.setColor(PotatoColor::primary);
		graphics.drawCircle(ftec::Circlef(
			center,
			radius
		), true);

		graphics.setColor(ftec::Color32::white());
		graphics.setLineWidth(2.0f);
		graphics.drawLine(ftec::Line2f(
			center + ftec::Vector2f(cos(angle), sin(angle)) * (radius - KNOB_LENGTH),
			center + ftec::Vector2f(cos(angle), sin(angle)) * radius
		));

		graphics.setLineWidth(1.0f);
	}

	void Knob::onDrag(Event & event)
	{
		m_Value += event.getMouseDelta().y / SENSITIVITY;
		m_Value = ftec::clamp(0.0f, 1.0f, m_Value);
	}

	Size Knob::getPreferredSize()
	{
		return Size(32, 32);
	}

}
