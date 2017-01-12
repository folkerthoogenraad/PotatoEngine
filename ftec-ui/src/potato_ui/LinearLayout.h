#pragma once

#include "Panel.h"

namespace potato {
	class LinearLayout : public Panel {
	public:
		enum LayoutDirection {
			HORIZONTAL,
			VERTICAL
		};
	protected:
		LayoutDirection m_DiRectangleion;
	public:
		LinearLayout(LayoutDirection dir);

		void updateLayout() override;
		void addPanel(std::shared_ptr<Panel> panel);

		Size getPreferredSize() override;
	};
}