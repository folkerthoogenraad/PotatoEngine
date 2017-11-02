#include "Button.h"

#include "graphics/Graphics2D.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

#include "logger/log.h"

namespace potato {
	Button::Button(std::shared_ptr<ftec::EngineContext> context, const std::string &text) : Panel(context), m_Text(text)
	{
		m_Focusable = true;
	}

	void Button::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		graphics.setFont(m_Font);
		//Don't call our super class, if we have children, we should ignore them
		//Actually, we should throw an error TODO

		Bounds bounds = getGlobalBounds();

		if (isPressed()) {
			graphics.setColor(style.m_AccentColor);
		}
		else {
			graphics.setColor(style.m_DarkBackground);
		}

		graphics.drawRectangle(bounds, true);

		if (isPressed()) {
			graphics.setColor(style.m_DarkBackground);
		}
		else {
			graphics.setColor(style.m_PrimaryColor);
		}

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
