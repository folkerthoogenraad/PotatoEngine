#pragma once

#include "potato_ui/Canvas.h"

namespace ftec {

	class VonoroiCanvas : public potato::Canvas {
	public:
		VonoroiCanvas();

		void update() override;
		void drawSelf(Graphics2D &graphics) override;

	};
}