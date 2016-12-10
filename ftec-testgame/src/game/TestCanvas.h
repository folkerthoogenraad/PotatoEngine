#pragma once

#include "potato_ui/Canvas.h"

namespace ftec {

	class TestCanvas : public potato::Canvas {
	public:
		TestCanvas();

		void update() override;
		void drawSelf(Graphics2D &graphics) override;

	};
}