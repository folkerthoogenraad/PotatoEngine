#include "Panel.h"

#include "graphics/Graphics2D.h"
#include "graphics/Font.h"

#include "engine/Input.h"
#include "engine/Engine.h"

#include "logger/log.h"

#include "resources/ResourceManager.h"

#include "engine/Keycodes.h"

namespace potato {
	Panel::Panel()
	{
		m_Font = ftec::Engine::getResourceManager().load<ftec::Font>("fonts/Ubuntu.ttf");
	}

	Bounds Panel::getGlobalBounds()
	{
		Bounds b = getGlobalOutline();
		return Bounds(
			b.x() + m_Insets.left,b.y() + m_Insets.top,
			b.width() - m_Insets.right - m_Insets.left, b.height() - m_Insets.bottom - m_Insets.top
		);
	}

	Bounds Panel::getGlobalOutline()
	{
		ftec::Vector2i p = m_LocalBounds.position;

		if (m_Parent) {
			p += m_Parent->getGlobalBounds().position;
		}

		return Bounds(
			p.x, p.y,
			m_LocalBounds.width(), m_LocalBounds.height()
		);
	}

	void Panel::draw(ftec::Graphics2D & graphics)
	{
		drawSelf(graphics);
		//Draw children
		for (auto child : m_Children) {
			child->draw(graphics);
		}
	}

	void Panel::drawSelf(ftec::Graphics2D & graphics)
	{
		if (m_Opaque) {
			graphics.setColor(m_BackgroundColor);
			graphics.drawRectangle(getGlobalBounds(), true);
		}
	}


	void Panel::process(Event &event)
	{
		for (auto child : m_Children) {
			if (!event.isConsumed()) {
				child->process(event);
			}
			else {
				//No point in looping any further
				break;
			}
		}

		if (event.isConsumed())
			return;

		//If the event is still not consumed by one of our children,
		//we might be able to use it ourselfs!
		processSelf(event);

	}

	void Panel::processSelf(Event &event)
	{
		//Hovering inputs
		if (event.getType() == EventType::MOUSE_MOVE
			|| event.getType() == EventType::MOUSE_DRAG) {

			bool hover = inBounds(event.getMousePosition());
			bool childHover = inChildBounds(event.getMousePosition());

			m_ChildHovering = childHover;

			if (hover && !m_Hovering) {
				m_Hovering = hover;
				onHoverEnter();
			}
			else if (!hover && m_Hovering) {
				m_Hovering = hover;
				onHoverLeave();
			}
		}

		{
			if (isHoveringSelf()) {
				if (ftec::Input::isMouseButtonPressed(MOUSE_BUTTON_1)) {
					m_Pressed = true;
					if (m_Focusable) {
						m_Focus = true;
					}
				}
				if (m_Pressed && ftec::Input::isMouseButtonReleased(MOUSE_BUTTON_1)) {
					m_Pressed = false; //Maybe a m_Clicked for one frame?
					onClick();
				}
			}
			else {
				//I see how this can become a big fucking bug if someone swallows the release event
				//Well, just pray to lord jezus christ in heaven that noone ever swallows the release event

				//cancel the press when its released outside the panel
				if (m_Pressed && ftec::Input::isMouseButtonReleased(MOUSE_BUTTON_1)) {
					m_Pressed = false;
				}
				if (ftec::Input::isMouseButtonPressed(MOUSE_BUTTON_1)) {
					m_Focus = false;
				}
			}
		}

		//Tabbing between focus things
		{
			if (ftec::Input::isKeyTyped(KEY_TAB)) {
				switchFocus();
			}
		}
	}

	void Panel::update()
	{
		//Update children
		for (auto child : m_Children) {
			child->update();
		}
	}

	void Panel::onClick()
	{
	}

	void Panel::onHoverEnter()
	{
	}

	void Panel::onHoverLeave()
	{
	}

	void Panel::switchFocus()
	{
		//TODO optimize this function with only one loop (keep track of first focusable index, and next after current)
		if (m_Children.size() == 0)
			return;

		int currentFocus = -1;
		int idx = 0;
		int focusCount = 0;

		//Find the child with focus
		for (auto c : m_Children) {
			if (c->m_Focus) {
				currentFocus = idx;
				focusCount++;
			}
			idx++;
		}
		
		//If there currently is nothing focussed
		if (focusCount == 0) {
			return;
		}if (focusCount > 1)
			LOG_ERROR("Focus count > 1");
		
		//Unfocus the current focus
		m_Children[currentFocus]->m_Focus = false;

		//See if we can find a next target to focus
		for (int i = currentFocus + 1; i < m_Children.size(); i++) {
			if (m_Children[i]->isFocusable()) {
				//if we can, we return
				m_Children[i]->m_Focus = true;
				return;
			}
		}

		//If we can't, we look for our next target!
		for (auto c : m_Children) {
			if (c->m_Focusable) {
				c->m_Focus = true;
				return;
			}
		}
	}

	bool Panel::inBounds(ftec::Vector2i point)
	{
		return getGlobalBounds().contains(point);
	}
	bool Panel::inChildBounds(ftec::Vector2i point)
	{
		//If not in our bounds, it certainly is not in our childs bounds
		if (!inBounds(point))
			return false;

		for (auto c : m_Children) {
			if (c->inBounds(point)) {
				return true;
			}
		}

		return false;
	}
	bool Panel::inSelfBounds(ftec::Vector2i point)
	{
		return inBounds(point) && !inChildBounds(point);
	}

	void Panel::requestUpdateLayout()
	{
		if (m_Parent)
			m_Parent->requestUpdateLayout();
		else
			updateLayout();
	}

	void Panel::updateLayout()
	{
		for (auto child : m_Children) {
			child->updateLayout();
		}
	}

	void Panel::setParent(Panel * parent)
	{
		this->m_Parent = parent;
		requestUpdateLayout();
	}
	
}
