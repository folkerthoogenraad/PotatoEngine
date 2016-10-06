#include "Button.h"

#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

namespace potato {
	Button::Button()
	{
		m_Focusable = true;
	}

	void Button::drawSelf(ftec::Graphics2D & graphics)
	{
		graphics.setFont(m_Font);
		//Don't call our super class, if we have children, we should ignore them
		//Actually, we should throw an error TODO

		if (m_Hovering) {
			if (m_Pressed) {
				graphics.setColor(PotatoColor::primary);
			}
			else {
				graphics.setColor(PotatoColor::lightPrimary);
			}
		}
		else {
			graphics.setColor(PotatoColor::lightPrimary);
		}

		graphics.drawRectangle(m_Bounds, true);

		if (m_Focus) {
			graphics.setColor(PotatoColor::darkPrimary);
			graphics.drawRectangle(m_Bounds, false);
		}

		graphics.setColor(PotatoColor::primaryText);

		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.setHorizontalAlign(ftec::FontAlign::CENTER);

		if (m_Pressed) {
			graphics.drawString(m_Text, m_Bounds.center() + ftec::vec2i(1, 1));
		}
		else {
			graphics.drawString(m_Text, m_Bounds.center());
		}
	}
	Size Button::getPreferredSize()
	{
		//TODO change these values based on the text and stuff
		return Size(128, 32);
	}
}
