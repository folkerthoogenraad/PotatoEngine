#pragma once

#include "potato_ui/Panel.h"

namespace potato {

	class Canvas : public Panel{
	public:

		virtual void update() override {};
		virtual void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override {};

		virtual potato::Size getPreferredSize() {
			return potato::Size(400,300);
		};
	};
}