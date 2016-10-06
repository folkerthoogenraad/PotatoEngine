#pragma once

#include <memory>
#include <vector>
#include "math/math.h"
#include "PotatoUI.h"
#include "logger/log.h"
#include "Event.h"

namespace ftec {
	class Graphics2D;
	class Font;
}

namespace potato {

	typedef ftec::rect2i Bounds;
	typedef ftec::vec2i Size;

	class Panel;
	class Panel {
	public:
		Bounds m_Bounds;
	protected:

		ftec::color32 m_BackgroundColor = ftec::color32::white();
		ftec::color32 m_ForegroundColor = ftec::color32::black();

		std::shared_ptr<ftec::Font> m_Font;

		bool m_Hovering = false;
		bool m_ChildHovering = false;

		bool m_Pressed = false;

		bool m_Focusable = false;
		bool m_Opaque = false;

		bool m_Focus = false;

		//Optional parent
		//shared ptr from this? maybe?
		Panel *m_Parent;
		std::weak_ptr<PotatoUI> m_UI;

		//List of children
		std::vector<std::shared_ptr<Panel>> m_Children;
	
	public:
		Panel();

		Bounds &bounds() { return m_Bounds; }
		const Bounds &bounds() const { return m_Bounds; }

		void opaque(bool op) { m_Opaque = op; }
		bool opaque() const { return m_Opaque; }

		void focusable(bool f) { m_Focusable = f; }
		bool focusable() const { return m_Focusable; }

		ftec::color32 &background() { return m_BackgroundColor; }
		const ftec::color32 &background() const { return m_BackgroundColor; }

		ftec::color32 &foreground() { return m_ForegroundColor; }
		const ftec::color32 &foreground() const { return m_ForegroundColor; }

		//Called each time the panel needs to be drawn
		virtual void draw(ftec::Graphics2D &graphics);
		virtual void drawSelf(ftec::Graphics2D &graphics);

		//Called each update (for animation, for everything)
		virtual void update();
		void process(Event &event);
		virtual void processSelf (Event &event);

		virtual void onClick();
		virtual void onHoverEnter();
		virtual void onHoverLeave();

		void switchFocus();

		bool isHovering() const { return m_Hovering; }
		bool isHoveringChild() const { return m_ChildHovering; }
		bool isHoveringSelf() const { return m_Hovering && !m_ChildHovering; }

		virtual Size getPreferredSize() { return m_Bounds.size; }

		bool inBounds(ftec::vec2i point);
		bool inChildBounds(ftec::vec2i point);
		bool inSelfBounds(ftec::vec2i point);

		//For layout overriding
		virtual void addPanel(std::shared_ptr<Panel> panel);

		//TODO make these weak_ptr
		void setParent(Panel *parent) { this->m_Parent = parent; }
		Panel *getParent() { return m_Parent; }

		void setUI(std::weak_ptr<PotatoUI> ui) {this->m_UI = ui; }
		std::weak_ptr<PotatoUI> getUI() { return this->m_UI; }

	};
}