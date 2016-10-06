#pragma once

#include "Panel.h"

namespace potato {
	class LinearLayout : public Panel {
	public:
		enum class LayoutDirection {
			HORIZONTAL,
			VERTICAL
		};
	protected:
		LayoutDirection m_Direction;
	public:
		LinearLayout(LayoutDirection dir);

		void addPanel(std::shared_ptr<Panel> panel) override;
		Size getPreferredSize() override;
	};
}