#include "Panel.h"

#include <assert.h>

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


	void Panel::preEvents()
	{
		for (auto child : m_Children) {
			child->preEvents();
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
		//Hover stuff
		if (event.isMotionEvent()) {
			bool hover = inBounds(event.getMousePosition());
			bool childHover = inChildBounds(event.getMousePosition());

			m_ChildHovering = childHover;

			if (hover && !m_Hovering) {
				m_Hovering = hover;
				onHoverEnter(event);
			}
			else if (!hover && m_Hovering) {
				m_Hovering = hover;
				onHoverLeave(event);
			}

			//Hover or drag pls
			if(isHoveringSelf() || isPressed())
				onHoverOrDrag(event);
		}

		//Move event
		if (event.getType() == EventType::MOUSE_MOVE) {
			if (isHoveringSelf()) {
				onHover(event);
			}
		}
		
		//Drag event
		if (event.getType() == EventType::MOUSE_DRAG) {
			if (isHoveringSelf() || isPressed()) {
				onDrag(event);
			}
		}

		//Press event
		if (event.getType() == EventType::MOUSE_PRESSED) {
			if (isHoveringSelf()){
				m_Pressed = true;
				if (m_Focusable) {
					m_Focus = true;
				}
				onMousePressed(event);
			}
			else {
				m_Pressed = false;
				m_Focus = false;
			}
		}

		//Release event
		if (event.getType() == EventType::MOUSE_RELEASED){
			if (isHoveringSelf()) {
				if (m_Pressed) {
					m_Pressed = false;
					onClick(event);
				}
				onMouseReleased(event);
			}
			else {
				if (m_Pressed)
				{
					m_Pressed = false;
					onMouseReleased(event);
				}
			}
		}

		//Typed keys
		if (event.getType() == EventType::KEYBOARD_TYPED) {
			if (isFocussed()) {
				if (event.getKeyCode() == KEY_TAB && !m_SwallowTab) {
					switchFocus();
				}
				else {
					onKeyTyped(event);
				}
			}
		}
	
		//Keyboard press events
		if (event.getType() == EventType::KEYBOARD_PRESSED) {
			if (isFocussed()) {
				onKeyPressed(event);
			}
		}

		//Keyboard press events
		if (event.getType() == EventType::KEYBOARD_RELEASED) {
			if (isFocussed()) {
				onKeyReleased(event);
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

	void Panel::onClick(Event & evt)
	{
		//Can be multiple events (like, keyboard type enter and stuff)
	}

	void Panel::onHoverEnter(Event & evt)
	{
		assert(evt.isMotionEvent());
	}

	void Panel::onHoverLeave(Event & evt)
	{
		assert(evt.isMotionEvent());
	}

	void Panel::onHover(Event & evt)
	{
		assert(evt.getType() == EventType::MOUSE_MOVE);
	}

	void Panel::onDrag(Event & evt)
	{
		assert(evt.getType() == EventType::MOUSE_DRAG);
	}

	void Panel::onHoverOrDrag(Event & evt)
	{
		assert(evt.isMotionEvent());
	}

	void Panel::onMouseReleased(Event & evt)
	{
		assert(evt.getType() == EventType::MOUSE_RELEASED);
	}

	void Panel::onMousePressed(Event & evt)
	{
		assert(evt.getType() == EventType::MOUSE_PRESSED);
	}

	void Panel::onKeyTyped(Event & evt)
	{
		assert(evt.getType() == EventType::KEYBOARD_TYPED);
	}

	void Panel::onKeyPressed(Event & evt)
	{
		assert(evt.getType() == EventType::KEYBOARD_PRESSED);
	}

	void Panel::onKeyReleased(Event & evt)
	{
		assert(evt.getType() == EventType::KEYBOARD_RELEASED);
	}

	void Panel::onFocusGain(Event & evt)
	{
		//Can be different ways
	}

	void Panel::onFocusLose(Event & evt)
	{
		//Can be multiple ways

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
