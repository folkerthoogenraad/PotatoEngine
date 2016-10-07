#include "List.h"
#include "graphics/Font.h"
#include "logger/log.h"
#include "engine/Input.h"

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
			graphics.drawString(s, ftec::vec2f(bounds.left(), bounds.top() + offset));
			offset += 16.f;
		}
	}

	void List::processSelf(Event & event)
	{
		Panel::processSelf(event);
		
		if (ftec::Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
			if (isHoveringSelf()) {
				//TODO callbacks, all that goodstuff
				event.consume();
			}
			else {
				if (auto ui = m_UI.lock()) {
					//This calles our destructor, which is nice :') /s
					//This can break lots of things if used incorrectly.
					//Luckally we proccess our events as last (children first)
					//If children are processed first we must find a workaroudn for this.
					ui->setContextMenu(nullptr);
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
