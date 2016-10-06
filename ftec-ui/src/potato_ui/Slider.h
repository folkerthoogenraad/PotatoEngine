#pragma once
#include "Panel.h"

namespace potato {

	class Slider : public Panel {
	protected:
		float m_Value = 0.0f;
		int m_Steps = -1;
		bool m_SliderHold = false;
	public:
		Slider();

		void drawSelf(ftec::Graphics2D &graphics) override;
		void update() override;

		float getValue() { return m_Value; }
		void setValue(float f) { m_Value = f; }

		int getSteps() { return m_Steps; }
		void setSteps(int steps) { m_Steps = steps; }

	protected:
		ftec::rect2f getSliderBounds();
	};

}