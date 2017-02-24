#include "Button.h"

#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

namespace potato {
	Button::Button(const std::string &text) : m_Text(text)
	{
		m_Focusable = true;
	}

	void Button::drawSelf(ftec::Graphics2D & graphics)
	{
		graphics.setFont(m_Font);
		//Don't call our super class, if we have children, we should ignore them
		//Actually, we should throw an error TODO

		Bounds bounds = getGlobalBounds();

		if (isHoveringSelf()) {
			if (isPressed()) {
				graphics.setColor(PotatoColor::primary);
			}
			else {
				graphics.setColor(PotatoColor::lightPrimary);
			}
		}
		else {
			graphics.setColor(PotatoColor::lightPrimary);
		}

		graphics.drawRectangle(bounds, true);

		if (isFocussed()) {
			graphics.setColor(PotatoColor::darkPrimary);
			graphics.drawRectangle(bounds, false);
		}

		graphics.setColor(PotatoColor::primaryText);

		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.setHorizontalAlign(ftec::FontAlign::CENTER);

		if (isPressed()) {
			graphics.drawString(m_Text, bounds.center() + ftec::Vector2i(1, 1));
		}
		else {
			graphics.drawString(m_Text, bounds.center());
		}
	}
	Size Button::getPreferredSize()
	{
		//TODO change these values based on the text and stuff
		return Size(128, 32);
	}
}
