#pragma once
#include <memory>
#include <vector>
#include "Layout.h"
#include "math/math.h"

namespace ftec {
	class Graphics2D;
}

namespace potato {

	class Event;

	struct Dimension {
		int width;
		int heigth;

		ftec::vec2 toVector();
	};

	struct Position {
		int x;
		int y;

		ftec::vec2 toVector();
	};

	class Panel {
	protected:
		Dimension m_Size;
		Position m_Position;

		ftec::vec4 m_BackgroundColor = ftec::vec4::white();

		bool m_Opaque;

		std::shared_ptr<Layout> m_Layout;

		//Optional parent
		std::weak_ptr<Panel> m_Parent;

		//List of children
		std::vector<std::shared_ptr<Panel>> m_Children;
	
	public:
		Dimension &size() { return m_Size; }
		const Dimension &size() const { return m_Size; }

		Position &position() { return m_Position; }
		const Position &position() const { return m_Position; }

		void opaque(bool op) { m_Opaque = op; }
		bool opaque() const { return m_Opaque; }

		//Called each time the panel needs to be drawn
		virtual void draw(ftec::Graphics2D &graphics);

		//Called each time an update is needed, this is only called when continues update is enabled
		virtual void update();

		//Called each time an event is here
		virtual void process(Event &event);

		void setLayout(std::shared_ptr<Layout> layout) { this->m_Layout = layout; }
		void addPanel(std::shared_ptr<Panel> panel) { this->m_Children.push_back(panel); }

		void setParent(std::weak_ptr<Panel> parent) { this->m_Parent = parent; }
		std::weak_ptr<Panel> getParent() { return m_Parent; }
	};
}