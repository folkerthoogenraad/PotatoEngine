#pragma once

#include "Panel.h"

namespace potato {
	class LinearLayout : public Panel {
	public:
		enum LayoutDiRectangleion {
			HORIZONTAL,
			VERTICAL
		};
	protected:
		LayoutDiRectangleion m_DiRectangleion;
	public:
		LinearLayout(LayoutDiRectangleion dir);

		void updateLayout() override;
		void addPanel(std::shared_ptr<Panel> panel);

		Size getPreferredSize() override;
	};
}