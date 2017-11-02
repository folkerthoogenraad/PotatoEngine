#include "Label.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

namespace potato {

	Label::Label(std::shared_ptr<ftec::EngineContext> context, const std::string text) : Panel(context), m_Text(text)
	{
	}

	void Label::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Panel::drawSelf(graphics, style);
		graphics.setColor(style.m_PrimaryColor);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.drawString(m_Text, getGlobalBounds().centerLeft());
	}

	Size Label::getPreferredSize()
	{
		return Size(128,32);
	}
}
