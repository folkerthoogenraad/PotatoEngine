#pragma once

#include "potato_ui/Canvas.h"

namespace ftec {

	class StairArcCanvas : public potato::Canvas {
	public:
		StairArcCanvas();

		void update() override;
		void drawSelf(Graphics2D &graphics) override;

	};
}