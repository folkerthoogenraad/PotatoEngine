#pragma once

#include "potato_ui/Canvas.h"

namespace ftec {

	class VoronoiCanvas : public potato::Canvas {
	public:
		VoronoiCanvas();

		void update() override;
		void drawSelf(Graphics2D &graphics, const potato::PotatoStyle& style) override;

	};
}