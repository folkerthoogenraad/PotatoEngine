#include "Label.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "PotatoUI.h"

namespace potato {

	Label::Label(const std::string text) : m_Text(text)
	{
	}

	void Label::drawSelf(ftec::Graphics2D & graphics)
	{
		Panel::drawSelf(graphics);
		graphics.setColor(PotatoColor::primaryText);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.drawString(m_Text, getGlobalBounds().centerLeft());
	}

	Size Label::getPreferredSize()
	{
		return Size(128,32);
	}
}
