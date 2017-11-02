#pragma once

#include "potato_ui/Canvas.h"

namespace ftec {

	class VoronoiCanvas : public potato::Canvas {
	public:
		VoronoiCanvas(std::shared_ptr<EngineContext> context);

		void update() override;
		void drawSelf(Graphics2D &graphics, const potato::PotatoStyle& style) override;

	};
}