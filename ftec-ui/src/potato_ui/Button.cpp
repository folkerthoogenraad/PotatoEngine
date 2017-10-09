#include "Button.h"

#include "graphics/Graphics2D.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

#include "logger/log.h"

namespace potato {
	Button::Button(const std::string &text) : m_Text(text)
	{
		m_Focusable = true;
	}

	void Button::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		graphics.setFont(m_Font);
		//Don't call our super class, if we have children, we should ignore them
		//Actually, we should throw an error TODO

		Bounds bounds = getGlobalBounds();

		const ftec::Sprite &background = style.getSprite(ftec::const_hash("ButtonBackground"));

		if (isHoveringSelf()) {
			if (isPressed()) {
				graphics.setColor(style.getColor(ftec::const_hash(COLOR_PRIMARY_DARK)));
			}
			else {
				graphics.setColor(style.getColor(ftec::const_hash(COLOR_PRIMARY_MEDIUM)));
			}
		}
		else {
			graphics.setColor(style.getColor(ftec::const_hash(COLOR_PRIMARY_MEDIUM)));
		}

		graphics.drawSprite(background, bounds);

		graphics.setColor(style.getColor(ftec::const_hash(COLOR_TEXT_LIGHT)));

		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.setHorizontalAlign(ftec::FontAlign::CENTER);

		graphics.drawString(m_Text, bounds.center());
	}
	Size Button::getPreferredSize()
	{
		//TODO change these values based on the text and stuff
		return Size(128, 32);
	}
}
