#pragma once

#include "Panel.h"

namespace potato {
	class SceneView : public Panel {
	public:
		SceneView();
		~SceneView() = default;

		virtual void draw(ftec::Graphics2D &graphics) override;
		virtual void update() override;
	};
}