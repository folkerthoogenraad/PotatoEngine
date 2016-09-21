#include "Panel.h"
#include "math/math.h"
#include "graphics/Graphics2D.h"

namespace potato {
	ftec::vec2 Dimension::toVector()
	{
		return ftec::vec2(width, heigth);
	}
	ftec::vec2 Position::toVector()
	{
		return ftec::vec2(x,y);
	}
	void Panel::draw(ftec::Graphics2D & graphics)
	{
		//Draw self

		//Draw children
		for (auto child : m_Children) {
			child->draw(graphics);
		}
	}

	void Panel::update()
	{
		//Do nothing here, but its virtual, so thats okay.
		for (auto child : m_Children) {
			child->update();
		}
	}

	void Panel::process(Event & event)
	{

	}
}
