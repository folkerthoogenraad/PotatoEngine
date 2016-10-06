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

	void TextField::processSelf(Event &event)
	{
		Panel::processSelf(event);

		if (m_Focus) {
			m_EditText.keyboardInput();
		}
	}

	void TextField::draw(ftec::Graphics2D & graphics)
	{
		graphics.setClip(m_Bounds);

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

		//A bit of alpha here
		if(m_Focus)
			graphics.setColor(ftec::color32(0x81, 0x22, 0x22, 0x88));
		else
			graphics.setColor(ftec::color32(0x81, 0x22, 0x22, 0x33));

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

		graphics.resetClip();
	}
}
