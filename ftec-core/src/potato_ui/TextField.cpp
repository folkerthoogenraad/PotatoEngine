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
			m_EditText.parseInput();
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

		if (m_EditText.length() == 0) {
			graphics.setColor(PotatoColor::secondaryText);
			graphics.drawString(m_Hint, ftec::vec2f(m_Bounds.x(), m_Bounds.center().y));
		}
		else {
			graphics.setColor(PotatoColor::primaryText);
			graphics.drawString(m_EditText.m_Text, ftec::vec2f(m_Bounds.x(), m_Bounds.center().y));
		}

		if (m_Focus) {
			//A bit of alpha here
			graphics.setColor(ftec::color32(0xFF,0xFF,0xFF,0x88));

			auto start = m_Font->measure(m_EditText.m_Text.substr(0, m_EditText.selectionStart())).x - 1;
			auto end = m_Font->measure(m_EditText.m_Text.substr(0, m_EditText.selectionEnd())).x + 1;
			auto center = m_Bounds.center();

			graphics.drawRectangle(
				ftec::rect2f(
					m_Bounds.x() + start,
					center.y - m_Font->getSize()/2,
					end - start,
					m_Font->getSize()
				),
				true
			);
		}

	}
}
