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

		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::TOP);
		graphics.setColor(PotatoColor::primaryText);

		float offset = 0;

		for (auto &s : m_TextOptions) {
			graphics.drawString(s, ftec::vec2f(m_Bounds.left(), m_Bounds.top() + offset));
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
					//This calles our destructor, which is nice :')
					ui->setContextMenu(nullptr);
					//Now we must consume the event, else the panel will call all the children and that will break the living shit out of everything because the destructor has already been called.
					event.consume();
				}
			}
		}
	}
}
