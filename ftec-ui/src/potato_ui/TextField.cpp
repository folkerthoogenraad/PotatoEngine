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

	void TextField::drawSelf(ftec::Graphics2D & graphics)
	{
		//TODO manage to find a solution for this
		//graphics.setClip(getGlobalOutline());
		Bounds bounds = getGlobalBounds();

		graphics.setFont(m_Font);
		graphics.setColor(PotatoColor::lightPrimary);

		graphics.drawRectangle(bounds, true);

		if (m_Focus) {
			graphics.setColor(PotatoColor::primary);
			graphics.drawRectangle(bounds, false);
		}

		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);

		if (m_EditText.length() == 0) {
			graphics.setColor(PotatoColor::secondaryText);
			graphics.drawString(m_Hint, ftec::Vector2i(bounds.x(), bounds.center().y));
		}
		else {
			graphics.setColor(PotatoColor::primaryText);
			graphics.drawString(m_EditText.m_Text, ftec::Vector2i(bounds.x(), bounds.center().y));
		}

		//A bit of alpha here
		if(m_Focus)
			graphics.setColor(ftec::Color32(0x81, 0x22, 0x22, 0x88));
		else
			graphics.setColor(ftec::Color32(0x81, 0x22, 0x22, 0x33));

		auto start = m_Font->measure(m_EditText.m_Text.substr(0, m_EditText.selectionStart())).x - 1;
		auto end = m_Font->measure(m_EditText.m_Text.substr(0, m_EditText.selectionEnd())).x + 1;
		auto center = bounds.center();

		graphics.drawRectangle(
			ftec::Rectanglef(
				bounds.x() + start,
				center.y - m_Font->getSize()/2,
				end - start,
				m_Font->getSize()
			),
			true
		);

		//TODO see top of function
		//graphics.resetClip();
	}
	Size TextField::getPreferredSize()
	{
		//TODO change these accoringly
		return Size(128,32);
	}
}
