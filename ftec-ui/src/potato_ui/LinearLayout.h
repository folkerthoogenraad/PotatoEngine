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
		LayoutDirection m_Direction;
	public:
		LinearLayout(LayoutDirection dir);

		void addPanel(std::shared_ptr<Panel> panel) override;
		void setParent(Panel *parent) override;
		Size getPreferredSize() override;
	};
}