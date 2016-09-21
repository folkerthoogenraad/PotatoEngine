#pragma once
#include <memory>
#include <vector>
#include "Layout.h"
#include "math/math.h"

namespace potato {

	struct Dimension {
		int width;
		int heigth;

		ftec::vec2 toVector() { return ftec::vec2(width, heigth); };
	};

	struct Position {
		int x;
		int y;

		ftec::vec2 toVector() { return ftec::vec2(x, y); };
	};

	class Panel {
	protected:
		Dimension m_Size;
		Position m_Position;

		std::shared_ptr<Layout> m_Layout;
		std::vector<std::shared_ptr<Panel>> m_Panels;
	
	public:
		Dimension &getSize() { return m_Size; }
		const Dimension &getSize() const { return m_Size; }

		Position &getPosition() { return m_Position; }
		const Position &getPosition() const { return m_Position; }

		void setLayout(std::shared_ptr<Layout> layout) { this->m_Layout = layout; }
		void addPanel(std::shared_ptr<Panel> panel) { this->m_Panels.push_back(panel); }
	};
}