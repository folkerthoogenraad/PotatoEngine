#include "Checkbox.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

namespace potato {

	Checkbox::Checkbox(std::shared_ptr<ftec::EngineContext> context) : Panel(context), m_Checked(false)
	{
		m_Focusable = true;
	}

	void Checkbox::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Panel::drawSelf(graphics, style);

		Bounds bounds = getGlobalBounds();

		//TODO center all these things
		ftec::Vector2i center = bounds.center();

		float height = (float) bounds.height();
		const float margin = 4;

		if (m_Checked) {
			graphics.setColor(style.m_AccentColor);
		}
		else {
			graphics.setColor(style.m_DarkBackground);
		}

		graphics.setCirclePrecision(4);
		graphics.setRoundedRectangleRadius(4);

		graphics.drawRoundedRectangle(ftec::Rectanglef((float)bounds.left(), (float)bounds.top(), height * 2.0f, height), true);

		graphics.setColor(style.m_BackgroundColor);

		graphics.drawRoundedRectangle(ftec::Rectanglef(
			(float)bounds.left() + margin + (m_Checked ? height : 0), 
			(float)bounds.top() + margin, 
			height - margin * 2, 
			height - margin * 2), true);


		graphics.setColor(style.m_PrimaryColor);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.drawString(m_Text, ftec::Vector2f((float)bounds.left() + height * 2.0f + 4.0f, (float)center.y));
	}

	void Checkbox::onClick(ftec::Event &event)
	{
		setChecked(!isChecked());
	}
	Size Checkbox::getPreferredSize()
	{
		//TODO change these values accordingly
		return Size(128,32);
	}
}
