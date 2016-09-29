#include "TextField.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "engine/Input.h"
#include "PotatoUI.h"

namespace potato {
	TextField::TextField()
	{
		m_Focusable = true;
	}

	void TextField::update()
	{
		Panel::update();

		if (m_Focus) {
			Panel::inputEditText(m_Text, m_CursorPosition);
		}
	}

	void TextField::draw(ftec::Graphics2D & graphics)
	{
		graphics.setFont(m_Font);
		graphics.setColor(PotatoColor::lightPrimary);

		graphics.drawRectangle(m_Bounds, true);

		if (m_Focus) {
			graphics.setColor(PotatoColor::primary);
			graphics.drawRectangle(m_Bounds, false);
		}

		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);

		if (m_Text.length() == 0) {
			graphics.setColor(PotatoColor::secondaryText);
			graphics.drawString(m_Hint, ftec::vec2f(m_Bounds.x(), m_Bounds.center().y));
		}
		else {
			graphics.setColor(PotatoColor::primaryText);
			graphics.drawString(m_Text, ftec::vec2f(m_Bounds.x(), m_Bounds.center().y));
		}

		if (m_Focus) {
			graphics.setColor(PotatoColor::primaryText);
			
			auto size = m_Font->measure(m_Text.substr(0, m_CursorPosition));
			auto center = m_Bounds.center();

			graphics.drawLine(ftec::vec2i(m_Bounds.x() + size.x, center.y - m_Font->getSize()/2), ftec::vec2i(m_Bounds.x() + size.x, center.y + m_Font->getSize() / 2));
		}

	}
}
