#include "Panel.h"

#include <assert.h>

#include "graphics/Graphics2D.h"
#include "graphics/Font.h"

#include "engine/Input.h"

#include "logger/log.h"

#include "resources/ResourceManager.h"

#include "engine/Keycodes.h"

namespace potato {
	Panel::Panel(std::shared_ptr<ftec::EngineContext> context)
		:m_Context(context), m_UI(nullptr)
	{
		m_Font = context->getResourceManager().load<ftec::Font>("fonts/Ubuntu.ttf");
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

	void Panel::onClick(ftec::Event & evt)
	{
		//Can be multiple events (like, keyboard type enter and stuff)
	}

	void Panel::onHoverEnter(ftec::Event & evt)
	{
		assert(evt.isMotionEvent());
	}

	void Panel::onHoverLeave(ftec::Event & evt)
	{
		assert(evt.isMotionEvent());
	}

	void Panel::onHover(ftec::Event & evt)
	{
		assert(evt.getType() == ftec::EventType::MouseMove);
	}

	void Panel::onDrag(ftec::Event & evt)
	{
		assert(evt.getType() == ftec::EventType::MouseDrag);
	}

	void Panel::onHoverOrDrag(ftec::Event & evt)
	{
		assert(evt.isMotionEvent());
	}

	void Panel::onMouseReleased(ftec::Event & evt)
	{
		assert(evt.getType() == ftec::EventType::MouseReleased);
	}

	void Panel::onMousePressed(ftec::Event & evt)
	{
		assert(evt.getType() == ftec::EventType::MousePressed);
	}

	void Panel::onKeyTyped(ftec::Event & evt)
	{
		assert(evt.getType() == ftec::EventType::KeyboardTyped);
	}

	void Panel::onKeyPressed(ftec::Event & evt)
	{
		assert(evt.getType() == ftec::EventType::KeyboardPressed);
	}

	void Panel::onKeyReleased(ftec::Event & evt)
	{
		assert(evt.getType() == ftec::EventType::KeyboardReleased);
	}

	void Panel::onFocusGain(ftec::Event & evt)
	{
		//Can be different ways
	}

	void Panel::onFocusLose(ftec::Event & evt)
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
		repaint();
	}

	void Panel::repaint()
	{
		if (m_UI) {
			m_UI->repaint(getGlobalOutline());
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
