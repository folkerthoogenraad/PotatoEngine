#pragma once

#include "potato_ui/Panel.h"

namespace ftec {

	class Canvas : public potato::Panel{
		void update() override;
		void drawSelf(Graphics2D &graphics) override;

		virtual potato::Size getPreferredSize() {
			return potato::Size(400,300);
		};
	};
}