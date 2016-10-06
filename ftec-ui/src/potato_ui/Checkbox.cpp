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

		//TODO center all these things
		ftec::vec2i center = m_Bounds.center();

		graphics.setColor(PotatoColor::primary);
		graphics.drawRectangle(ftec::rect2f(m_Bounds.left(), center.y - 8, 16,16), true);
		if (m_Checked) {
			graphics.setColor(PotatoColor::accent);
			graphics.drawRectangle(ftec::rect2f(m_Bounds.left() + 4, center.y - 4, 8, 8), true);
		}

		graphics.setColor(PotatoColor::primaryText);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.drawString(m_Text, ftec::vec2f(m_Bounds.left() + 18, center.y));

		if (m_Focus) {
			graphics.setColor(PotatoColor::darkPrimary);
			graphics.drawRectangle(m_Bounds, false);
		}
	}

	void Checkbox::onClick()
	{
		m_Checked = !m_Checked;
	}
}
