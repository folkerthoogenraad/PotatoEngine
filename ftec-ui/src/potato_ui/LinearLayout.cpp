#include "LinearLayout.h"

#include "math/math.h"

namespace potato {
	LinearLayout::LinearLayout(LayoutDirection dir)
		: m_Direction(dir)
	{

	}

	void LinearLayout::addPanel(std::shared_ptr<Panel> panel)
	{
		Panel::addPanel(panel);

		Size t = getPreferredSize();
		Size pref = panel->getPreferredSize();

		//If the direction is horizontal
		if (m_Direction == LayoutDirection::HORIZONTAL) {
			panel->bounds() = ftec::rect2i(
				m_Bounds.x() + t.width,
				m_Bounds.y(),
				pref.width,
				t.height);
		}

		//If the direction is vertical
		else {
			panel->bounds() = ftec::rect2i(
				m_Bounds.x(),
				m_Bounds.y() + t.height,
				t.width,
				pref.height);
		}
	}

	Size LinearLayout::getPreferredSize()
	{
		Size s;
		
		for (auto &child : m_Children)
		{
			s += child->getPreferredSize();
		}

		//Horizontal layout = stacking horizontally
		if (m_Direction == LayoutDirection::HORIZONTAL) {
			return Size(s.x, m_Bounds.size.y);
		}
		//Vertical layout = stacking vertically
		else {
			return Size(m_Bounds.size.x, s.y);
		}
	}
}
