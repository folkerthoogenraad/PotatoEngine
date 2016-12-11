#include "Checkbox.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

namespace potato {

	Checkbox::Checkbox() : m_Checked(false)
	{
		m_Focusable = true;
	}

	void Checkbox::drawSelf(ftec::Graphics2D & graphics)
	{
		Panel::drawSelf(graphics);

		Bounds bounds = getGlobalBounds();

		//TODO center all these things
		ftec::Vector2i center = bounds.center();

		graphics.setColor(PotatoColor::primary);
		graphics.drawRectangle(ftec::Rectanglef((float)bounds.left(), (float)center.y - 8.0f, 16.0f,16.0f), true);
		if (m_Checked) {
			graphics.setColor(PotatoColor::accent);
			graphics.drawRectangle(ftec::Rectanglef((float)bounds.left() + 4.0f, (float)center.y - 4.0f, 8.0f, 8.0f), true);
		}

		graphics.setColor(PotatoColor::primaryText);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.drawString(m_Text, ftec::Vector2f((float)bounds.left() + 18.0f, (float)center.y));

		if (m_Focus) {
			graphics.setColor(PotatoColor::darkPrimary);
			graphics.drawRectangle(bounds, false);
		}
	}

	void Checkbox::onClick()
	{
		m_Checked = !m_Checked;
	}
	Size Checkbox::getPreferredSize()
	{
		//TODO change these values accordingly
		return Size(128,32);
	}
}
