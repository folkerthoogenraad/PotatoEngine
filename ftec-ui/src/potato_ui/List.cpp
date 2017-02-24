#include "List.h"
#include "graphics/Font.h"
#include "logger/log.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"


namespace potato {
	List::List()
	{
		m_Opaque = true;
		m_BackgroundColor = PotatoColor::lightPrimary;
	}

	void List::drawSelf(ftec::Graphics2D & graphics)
	{
		Panel::drawSelf(graphics);

		Bounds bounds = getGlobalBounds();

		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::TOP);
		graphics.setColor(PotatoColor::primaryText);

		float offset = 0;

		for (auto &s : m_TextOptions) {
			graphics.drawString(s, ftec::Vector2i(bounds.left(), bounds.top() + (int)offset));
			offset += 16.f;
		}
	}

	void List::processSelf(Event & event)
	{
		Panel::processSelf(event);
		
		if (ftec::Input::isMouseButtonDown(MOUSE_BUTTON_1)) {
			if (isHoveringSelf()) {
				//TODO callbacks, all that goodstuff
				event.consume();
			}
			else {
				if (m_UI) {
					//This calles our destructor, which is nice :') /s
					//This can break lots of things if used incorrectly.
					//Luckally we proccess our events as last (children first)
					//If children are processed first we must find a workaroudn for this.
					//TODO do that
					m_UI->setContextMenu(nullptr);
				}
			}
		}
	}
	Size List::getPreferredSize()
	{
		//TODO change these accoringly
		return Size(128,128);
	}
}
