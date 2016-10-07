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

		void updateLayout() override;

		Size getPreferredSize() override;
	};
}