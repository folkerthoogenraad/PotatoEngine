#include "Knob.h"
#include "math/math.h"
#include "logger/log.h"

namespace potato {

	static const float SENSITIVITY = -200.0f;
	static const float KNOB_LENGTH = 8.0f;
	static const float MIN_ANGLE = -PI - PI / 4;
	static const float MAX_ANGLE = PI / 4;

	static const float START_ANGLE = -PI / 2.0f;
	
	Knob::Knob(std::shared_ptr<ftec::EngineContext> context)
		:Panel(context)
	{
		m_Focusable = true;
	}

	void Knob::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Bounds b = getGlobalBounds();

		auto center = b.center();
		auto radius = ftec::min(b.width(), b.height()) / 2.0f;

		float v = m_Value;

		if(m_Steps > 1) 
			v = ftec::floor(m_Value * m_Steps) / m_Steps;

		graphics.setCirclePrecision(64);

		float thickness = (radius / 16.0f) * 4;
		float pointSize = (radius / 16.0f) * 2;

		graphics.setColor(style.m_DarkBackground);
		graphics.drawCircle(ftec::Circlef(
			center,
			radius
		), true);

		graphics.setColor(style.m_AccentColor);
		graphics.drawArc(
			center,
			radius, 
			true,
			START_ANGLE,
			v * PI * 2);

		graphics.setColor(style.m_BackgroundColor);
		graphics.drawCircle(ftec::Circlef(
			center,
			radius - thickness
		), true);

		auto angle = START_ANGLE + v * 2 * PI;

		graphics.setColor(style.m_PrimaryColor);
		graphics.setPointSize(pointSize);
		graphics.setPointType(ftec::Graphics2D::PointType::CIRCLE);
		graphics.setCirclePrecision(8);
		graphics.drawPoint(
			center + ftec::Vector2f(cos(angle) * (radius - thickness * 2), sin(angle) * (radius - thickness * 2))
			);

		graphics.setCirclePrecision(16);

	}

	void Knob::onDrag(ftec::Event & event)
	{
		m_Value += event.getMouseDelta().y / SENSITIVITY;
		m_Value = ftec::clamp(0.0f, 1.0f, m_Value);
	}

	Size Knob::getPreferredSize()
	{
		return Size(64, 64);
	}

}
