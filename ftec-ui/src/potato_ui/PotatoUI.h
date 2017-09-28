#pragma once

/*
Potato UI is a user interface system for realtime software. 
Every panel gets an update call every frame and, if needed, every panel
can redraw every frame.

This is not yet implemented, but will be implemented using OpenGL on the
PotatoEngine bases. The PotatoEngine will be fully compatible with the
PotatoUI (obviously).
*/

#include <string>

#include "graphics/Graphics2D.h"
#include "math/Vector2.h"

namespace potato {

	class Panel;
	class Event;

	class PotatoColor {
	public:PotatoColor() = delete; ~PotatoColor() = delete;
	public:
		static ftec::Color32 primaryText;
		static ftec::Color32 secondaryText;

		static ftec::Color32 darkPrimary;
		static ftec::Color32 primary;
		static ftec::Color32 lightPrimary;

		static ftec::Color32 divider;
		static ftec::Color32 accent;
		static ftec::Color32 iconsText;
	};

	class PotatoClipboard {
	private:
		static std::string data;
	public:
		static const std::string &getData();
		static void setData(const std::string &);
	};

	class PotatoUI;

	class PotatoUI : public std::enable_shared_from_this<PotatoUI> {
	private:
		ftec::Graphics2D m_Graphics;
		std::shared_ptr<Panel> m_Root;
		std::shared_ptr<Panel> m_ContextMenu;

		std::shared_ptr<Panel> m_Focus = nullptr;
		std::shared_ptr<Panel> m_Hover = nullptr;
		
		// 10 mouse buttons, might be a bit overkill :)
		std::array<std::shared_ptr<Panel>, 10> m_Pressed;

		ftec::Vector2f m_MouseStart;
	public:
		PotatoUI();
		~PotatoUI();
		void update();
		void render();
		
		void setRoot(std::shared_ptr<Panel> root);
		void setContextMenu(std::shared_ptr<Panel> contextMenu);

		// Oh, that is nasty with that event thing there (dirty code alert)
		void resetFocus(Event &event);

		Panel *getFocus() const { return m_Focus.get(); }
		bool isFocused(const Panel *panel) const { return m_Focus.get() == panel; }

		Panel *getHover() const { return m_Hover.get(); }
		bool isHovered(const Panel *panel) const { return m_Hover.get() == panel; }

		bool isPressed(const Panel *panel) const;
		bool isPressed(const Panel *panel, int mb) const;

	private:
		void processEvents(std::shared_ptr<Panel> panel, Event &event);

		void setFocusAndFireEvents(std::shared_ptr<Panel> focus, Event &event);
		void setHoverAndFireEvents(std::shared_ptr<Panel> hover, Event &event);
	};
}