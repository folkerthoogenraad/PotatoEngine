#pragma once

#include "Panel.h"

namespace potato {
	class Knob : public Panel {
	protected:
		float m_Value = 0.0f;
		int m_Steps = -1;
		bool m_SliderHold = false;
	public:
		Knob();

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;

		void onDrag(Event &event) override;

		float getValue() { return m_Value; }
		void setValue(float f) { m_Value = f; }

		int getSteps() { return m_Steps; }
		void setSteps(int steps) { m_Steps = steps; }

		Size getPreferredSize() override;
	};
}