#pragma once

#include "Panel.h"

namespace potato {
	class SceneView : public Panel {
	public:
		SceneView();
		~SceneView() = default;

		virtual void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		virtual void update() override;
		Size getPreferredSize() override;
	};
}