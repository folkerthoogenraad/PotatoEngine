#include "Panel.h"
#include "math/math.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "engine/Input.h"
#include "engine/Engine.h"
#include "logger/log.h"

namespace potato {
	Panel::Panel()
	{
		m_Font = ftec::Engine::getResourceManager().load<ftec::Font>("fonts/default14.fnt");
	}
	void Panel::draw(ftec::Graphics2D & graphics)
	{
		//Draw self
		if (m_Opaque) {
			graphics.setColor(m_BackgroundColor);
			graphics.drawRectangle(m_Bounds, true);
		}

		//Draw children
		for (auto child : m_Children) {
			child->draw(graphics);
		}
	}

	void Panel::update()
	{
		//Hovering inputs
		{
			bool hover = inBounds(ftec::Input::getMousePosition());
			bool childHover = inChildBounds(ftec::Input::getMousePosition());

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

		//Click inputs
		{
			if (isHoveringSelf()) {
				if (ftec::Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
					m_Pressed = true;
					if (m_Focusable) {
						m_Focus = true;
					}
				}
				if (m_Pressed && ftec::Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_1)) {
					m_Pressed = false; //Maybe a m_Clicked for one frame?
					onClick();
				}
			}
			else {
				//cancel the press when its released outside the panel
				if (m_Pressed && ftec::Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_1)) {
					m_Pressed = false;
				}
				if (ftec::Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
					m_Focus = false;
				}
			}
		}
		

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

	bool Panel::inBounds(ftec::vec2i point)
	{
		return m_Bounds.contains(point);
	}
	bool Panel::inChildBounds(ftec::vec2i point)
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
	bool Panel::inSelfBounds(ftec::vec2i point)
	{
		return inBounds(point) && !inChildBounds(point);
	}

	void Panel::addPanel(std::shared_ptr<Panel> panel)
	{
		this->m_Children.push_back(panel);
	}

	
}
