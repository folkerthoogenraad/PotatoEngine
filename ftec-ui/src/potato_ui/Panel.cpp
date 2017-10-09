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

	Bounds Panel::getInnerBounds() const 
	{
		Bounds b = localbounds();

		return Bounds(
			b.x() + m_Insets.left, b.y() + m_Insets.top,
			b.width() - m_Insets.right - m_Insets.left, b.height() - m_Insets.bottom - m_Insets.top
		);
	}

	Bounds Panel::getGlobalBounds() const
	{
		Bounds b = getGlobalOutline();
		return Bounds(
			b.x() + m_Insets.left,b.y() + m_Insets.top,
			b.width() - m_Insets.right - m_Insets.left, b.height() - m_Insets.bottom - m_Insets.top
		);
	}

	Bounds Panel::getGlobalOutline() const
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

	void Panel::draw(ftec::Graphics2D & graphics, const PotatoStyle &style)
	{
		drawSelf(graphics, style);
		//Draw children
		/*for (auto child : m_Children) {
			child->draw(graphics);
		}*/
		//Back to front

		auto childs = getChildren();

		for (auto it = childs.rbegin(); it != childs.rend(); it++)
		{
			(*it)->draw(graphics, style);
		}
	}

	void Panel::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle &style)
	{
		if (m_Opaque) {
			graphics.setColor(m_BackgroundColor);
			graphics.drawRectangle(getGlobalBounds(), true);
		}
	}


	void Panel::onPreEvents()
	{
		for (auto child : getChildren()) {
			child->onPreEvents();
		}
	}

	void Panel::onPostEvents() 
	{
		for (auto child : getChildren()) {
			child->onPostEvents();
		}
	}

	void Panel::update()
	{
		//Update children
		for (auto child : getChildren()) {
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
		// TODO not here.
	}

	bool Panel::isHovering() const
	{
		return isHoveringSelf() || isHoveringChild();
	}

	bool Panel::isHoveringChild() const
	{
		for (const auto &c : getChildren()) {
			if (c->isHovering())
				return true;
			if (c->isHoveringChild())
				return true;
		}
		return false;
	}

	bool Panel::isHoveringSelf() const
	{
		return m_UI && m_UI->isHovered(this);
	}

	bool Panel::isChildFocused() const
	{
		for (auto c : getChildren()) {
			if (c->isFocused())
				return true;
			if (c->isChildFocused())
				return true;
		}
		return false;
	}

	bool Panel::inBounds(ftec::Vector2i point) const
	{
		return getGlobalBounds().contains(point);
	}
	bool Panel::inChildBounds(ftec::Vector2i point) const
	{
		//If not in our bounds, it certainly is not in our childs bounds
		if (!inBounds(point))
			return false;

		for (auto c : getChildren()) {
			if (c->inBounds(point)) {
				return true;
			}
		}

		return false;
	}
	bool Panel::inSelfBounds(ftec::Vector2i point) const
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
		for (auto child : getChildren()) {
			child->updateLayout();
		}
	}

	void Panel::setUI(PotatoUI * ui)
	{
		m_UI = ui;

		for (auto c : getChildren()) {
			c->setUI(ui);
		}
	}

	void Panel::setParent(Panel * parent)
	{
		this->m_Parent = parent;
		requestUpdateLayout();
	}

	std::shared_ptr<Panel> Panel::findPanelByPosition(ftec::Vector2i input)
	{
		//Can't be itself, might still be a problem....

		for (auto p : getChildren()) {
			auto c = p->findPanelByPosition(input);
			if (c)
				return c;
		}
		if (inBounds(input))
			return shared_from_this();

		// Isn't found!
		return nullptr;
	}

	void Panel::initChild(std::shared_ptr<Panel> child)
	{
		child->setParent(this);
		child->setUI(m_UI);
		child->init();
	}
	
}
