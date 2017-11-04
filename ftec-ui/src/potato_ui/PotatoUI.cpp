#include "PotatoUI.h"
#include "Panel.h"
#include "logger/log.h"

#include "graphics/Window.h"
#include "graphics/Camera.h"

#include "engine/Event.h"

#include "engine/Keycodes.h"

#include "resources/ResourceManager.h"

#include "engine/Engine.h"

#include "math/collision.h"

namespace potato {
	//https://www.materialpalette.com/blue-grey/grey

	ftec::Color32 PotatoColor::primaryText =	ftec::Color32(0x21, 0x21, 0x21, 0xFF);
	ftec::Color32 PotatoColor::secondaryText =	ftec::Color32(0x75, 0x75, 0x75, 0xFF);

	ftec::Color32 PotatoColor::darkPrimary =	ftec::Color32(0x45, 0x5A, 0x64, 0xFF);
	ftec::Color32 PotatoColor::primary =		ftec::Color32(0x60, 0x7D, 0x8B, 0xFF);
	ftec::Color32 PotatoColor::lightPrimary =	ftec::Color32(0xCF, 0xD8, 0xDC, 0xFF);

	ftec::Color32 PotatoColor::divider =		ftec::Color32(0xBD, 0xBD, 0xBD, 0xFF);
	ftec::Color32 PotatoColor::accent =			ftec::Color32(0x9E, 0x9E, 0x9E, 0xFF);
	ftec::Color32 PotatoColor::iconsText =		ftec::Color32(0xFF, 0xFF, 0xFF, 0xFF);


	std::string PotatoClipboard::data = "";
	//TODO make this use the windows clipboard
	const std::string &PotatoClipboard::getData() {
		return data;
	}

	void PotatoClipboard::setData(const std::string &input) 
	{
		data = input;
	}

	PotatoUI::PotatoUI(std::shared_ptr<ftec::EngineContext> context)
		:m_Context(context), m_Graphics(context)
	{
		m_Graphics.m_Camera 
			= ftec::Camera::orthagonal(context->getWindow().getHeight(), context->getWindow().getWidth() / context->getWindow().getHeight(), -100, 100, true);
		m_Graphics.m_Camera.m_Position = ftec::Vector3f(context->getWindow().getWidth() / 2.0f, context->getWindow().getHeight() / 2.0f);
	}

	PotatoUI::~PotatoUI()
	{
	}

	void PotatoUI::update()	
	{
		m_Changed = false;

		if (m_Root) {

			// TODO this kinda is an event too
			// This should probably be handled differently but whatever, its good for now
			if (m_Context->getWindow().isResized()) {
				if (m_ContextMenu){
					m_ContextMenu->localbounds() = ftec::Rectanglei(0, 0, (int)m_Context->getWindow().getWidth(), (int)m_Context->getWindow().getHeight());
					m_ContextMenu->updateLayout();
				}

				m_Root->localbounds() = ftec::Rectanglei(0, 0, (int)m_Context->getWindow().getWidth(), (int)m_Context->getWindow().getHeight());
				m_Root->updateLayout();
			}

			//This has to be better, but whatever
			if (m_ContextMenu)
				m_ContextMenu->onPreEvents();

			m_Root->onPreEvents();

			// Copy the events, so they are editable
			std::vector<ftec::Event> events = m_Context->getInput().getEvents();

			for (auto event : events) {
				event.m_Consumed = false; // Just to be sure.

				if (m_ContextMenu)
					processEvents(m_ContextMenu, event);
				if (!event.isConsumed())
					processEvents(m_Root, event);
			}

			if (m_ContextMenu)
				m_ContextMenu->onPostEvents();

			m_Root->onPostEvents();

			if (m_ContextMenu)
				m_ContextMenu->update();

			m_Root->update();
		}
	}

	void PotatoUI::render()
	{
		float width = m_Context->getWindow().getWidth();
		float height = m_Context->getWindow().getHeight();

		//Always set the right size and stuff
		m_Graphics.m_Camera = ftec::Camera::orthagonal(height, width / height, -100, 100, true);
		m_Graphics.m_Camera.m_Position = ftec::Vector3f(width / 2.0f, height / 2.0f);

		if (GRAPHICS_COPY_SWAP) {
			m_Graphics.m_Camera.m_ClippingRectangle = ftec::Rectanglef(
				m_RepaintRectangle.x() / width,
				m_RepaintRectangle.y() / height,
				m_RepaintRectangle.width() / width,
				m_RepaintRectangle.height() / height
			);
		}
		else {
			m_Graphics.m_Camera.m_ClippingRectangle = ftec::Rectanglef(
				0,
				0,
				1,
				1
			);
		}

		m_Graphics.drawClear();
		m_Graphics.begin();

		if (m_Root) {
			m_Root->draw(m_Graphics, m_Style);
		}
		if (m_ContextMenu) {
			m_ContextMenu->draw(m_Graphics, m_Style);
		}

		m_Graphics.setColor(ftec::Color32(255, 0, 0, 75));
		//m_Graphics.drawRectangle(m_RepaintRectangle, true);

		m_Graphics.end();

		// Reset the repaint boolean
		m_Repaint = false;
		m_Changed = true;
	}

	void PotatoUI::repaint()
	{
		m_Repaint = true;
		m_RepaintRectangle = Bounds(0, 0, (int)m_Context->getWindow().getWidth(), (int)m_Context->getWindow().getHeight());
	}

	void PotatoUI::repaint(Bounds rectangle)
	{
		// If nothing else has called repaint yet
		if (!m_Repaint)
			m_RepaintRectangle = rectangle;

		// If the new rectangle is larger than the current rectangle
		else if (contains(rectangle, m_RepaintRectangle)) {
			m_RepaintRectangle = rectangle;
		}
		
		// If the current repaint rectangle already contains the current rectangle
		else if (contains(m_RepaintRectangle, rectangle)) {}

		// If its just different...
		else {
			m_RepaintRectangle = Bounds(0, 0, (int)m_Context->getWindow().getWidth(), (int)m_Context->getWindow().getHeight());
		}
		
		m_Repaint = true;
	}

	void PotatoUI::setRoot(std::shared_ptr<Panel> root)
	{
		m_Root = root;
		if (m_Root) {
			m_Root->setUI(this);
			//Give this the full panel, this happens always, at all times
			m_Root->localbounds() = ftec::Rectanglei(0, 0, (int)m_Context->getWindow().getWidth(), (int)m_Context->getWindow().getHeight());
			m_Root->updateLayout();
		}

		repaint();
	}

	void PotatoUI::setContextMenu(std::shared_ptr<Panel> contextMenu)
	{
		m_ContextMenu = contextMenu;
		if (m_ContextMenu) {
			m_ContextMenu->localbounds() = ftec::Rectanglei(0, 0, (int)m_Context->getWindow().getWidth(), (int)m_Context->getWindow().getHeight());
			m_ContextMenu->setUI(this);
		}

		repaint();
	}

	void PotatoUI::resetFocus(ftec::Event &event)
	{
		setFocusAndFireEvents(nullptr, event);
	}

	void PotatoUI::setFocusAndFireEvents(std::shared_ptr<Panel> focus, ftec::Event &event)
	{
		if (m_Focus == focus)
			return;

		if (m_Focus)
			m_Focus->onFocusGain(event);

		if (focus)
			focus->onFocusLose(event);

		m_Focus = focus;
	}

	void PotatoUI::setHoverAndFireEvents(std::shared_ptr<Panel> hover, ftec::Event &event)
	{
		if (m_Hover == hover)
			return;

		if (m_Hover)
			m_Hover->onHoverLeave(event);

		if (hover)
			hover->onHoverEnter(event);

		m_Hover = hover;
	}

	bool PotatoUI::isPressed(const Panel * panel) const
	{
		for (int i = 0; i < m_Pressed.size(); i++)
			if (isPressed(panel, i))
				return true;

		return false;
	}

	bool PotatoUI::isPressed(const Panel * panel, int mb) const
	{
		if (mb < 0 || mb > m_Pressed.size())
			return false;

		return m_Pressed[mb].get() == panel;
	}

	bool PotatoUI::shouldRepaint() const
	{
		return m_Repaint;
	}

	bool PotatoUI::hasChanged() const
	{
		return m_Changed;
	}

	PotatoStyle & PotatoUI::getStyle()
	{
		return m_Style;
	}

	void PotatoUI::processEvents(std::shared_ptr<Panel> panel, ftec::Event &event)
	{
		if (event.getType() == ftec::EventType::MOUSE_MOVE) {
			auto hover = panel->findPanelByPosition(event.getMousePosition());

			// Hover enter and hover leave
			setHoverAndFireEvents(hover, event);

			// Constant events
			if (m_Hover) {
				m_Hover->onHover(event);
				m_Hover->onHoverOrDrag(event);
				event.consume();
			}

		}

		if (event.getType() == ftec::EventType::MOUSE_DRAG) {
			auto m = m_Pressed[event.getMouseButton()];
			if (m) {
				m->onDrag(event);
				m->onHoverOrDrag(event);

				event.consume();
			}
		}

		// TODO keep track of what is pressed
		if (event.getType() == ftec::EventType::MOUSE_PRESSED) {
			m_Pressed[event.getMouseButton()] = m_Hover;

			if (m_Hover) {
				m_Hover->onMousePressed(event);

				if (m_Hover->isFocusable()) {
					setFocusAndFireEvents(m_Hover, event);
				}
				else {
					setFocusAndFireEvents(nullptr, event);
				}

				event.consume();
			}
		}

		// TODO and what is released here.
		if (event.getType() == ftec::EventType::MOUSE_RELEASED) {
			auto m = m_Pressed[event.getMouseButton()];

			// Reset
			m_Pressed[event.getMouseButton()] = nullptr;

			// TODO reassing the hover now

			if (m) {
				m->onMouseReleased(event);

				if(m->inBounds(event.getMousePosition())){
					m->onClick(event);
				}

				event.consume();
			}
		}


		// TODO tab switching
		if (event.getType() == ftec::EventType::KEYBOARD_TYPED) {
			if (m_Focus) {
				m_Focus->onKeyTyped(event);
			}
		}

		if (event.getType() == ftec::EventType::KEYBOARD_PRESSED) {
			if (m_Focus) {
				m_Focus->onKeyPressed(event);
			}
		}

		if (event.getType() == ftec::EventType::KEYBOARD_RELEASED) {
			if (m_Focus) {
				m_Focus->onKeyReleased(event);
			}
		}
	}

#if 0
	void PotatoUI::processEvents(std::shared_ptr<Panel> panel, ftec::Event & event)
	{
		auto children = panel->getChildren();

		for (auto child : children) {
			if (!event.isConsumed()) {
				processEvents(child, event);
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

		Panel &p = *panel;

		//Hover stuff
		/*if (event.isMotionEvent()) {
			bool hover = p.inBounds(event.getMousePosition());
			bool childHover = p.inChildBounds(event.getMousePosition());

			p.m_ChildHovering = childHover;

			if (hover && !p.m_Hovering) {
				p.m_Hovering = hover;
				p.onHoverEnter(event);
			}
			else if (!hover && p.m_Hovering) {
				p.m_Hovering = hover;
				p.onHoverLeave(event);
			}

			//Hover or drag pls
			if (p.isHoveringSelf() || p.isPressed())
				p.onHoverOrDrag(event);
		}*/

		if (event.isMotionEvent()) {
			bool hover = p.inBounds(event.getMousePosition());

			if (hover && !isHovered(panel.get())) {
				p.onHoverEnter(event);
				
				if (getHover())
					getHover()->onHoverLeave(event);

				setHover(panel.get());
				event.consume();
			}

			//Hover or drag pls
			if (p.isHoveringSelf() || p.isPressed())
				p.onHoverOrDrag(event);
		}

		//Move event
		if (event.getType() == EventType::MOUSE_MOVE) {
			if (p.isHoveringSelf()) {
				p.onHover(event);
			}
		}

		//Drag event
		if (event.getType() == EventType::MOUSE_DRAG) {
			if (p.isHoveringSelf() || p.isPressed()) {
				p.onDrag(event);
			}
		}

		//Press event
		if (event.getType() == EventType::MOUSE_PRESSED) {
			if (p.isHoveringSelf()) {
				p.m_Pressed = true; //Pressed should be handled by the UI as well...
				if (p.m_Focusable) {
					setFocus(panel.get());
				}
				p.onMousePressed(event);
			}
			else {
				p.m_Pressed = false;
			}
		}

		//Release event
		if (event.getType() == EventType::MOUSE_RELEASED) {
			if (p.isHoveringSelf()) {
				if (p.m_Pressed) {
					p.m_Pressed = false;
					p.onClick(event);
				}
				p.onMouseReleased(event);
			}
			else {
				if (p.m_Pressed)
				{
					p.m_Pressed = false;
					p.onMouseReleased(event);
				}
			}
		}

		//Typed keys
		if (event.getType() == EventType::KEYBOARD_TYPED) {
			if (isFocused(panel.get())) {
				if (event.getKeyCode() == KEY_TAB && !p.m_SwallowTab) {
					p.switchFocus();
				}
				else {
					p.onKeyTyped(event);
				}
			}
		}

		//Keyboard press events
		if (event.getType() == EventType::KEYBOARD_PRESSED) {
			if (isFocused(panel.get())) {
				p.onKeyPressed(event);
			}
		}

		//Keyboard press events
		if (event.getType() == EventType::KEYBOARD_RELEASED) {
			if (isFocused(panel.get())) {
				p.onKeyReleased(event);
			}
		}
	}

#endif

}
