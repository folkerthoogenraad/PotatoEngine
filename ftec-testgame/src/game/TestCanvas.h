#pragma once

#include "potato_ui/Canvas.h"

#include "graphics/2d/Renderer2D.h"

namespace ftec {

	class TestCanvas : public potato::Canvas {
		Renderer2D m_Renderer;
	public:
		TestCanvas();

		void update() override;
		void drawSelf(Graphics2D &graphics) override;

	};
}