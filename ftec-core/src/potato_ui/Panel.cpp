#include "Panel.h"
#include "math/math.h"
#include "graphics/Graphics2D.h"

namespace potato {

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
