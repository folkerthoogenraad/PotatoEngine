#pragma once

#include "Panel.h"

namespace potato {
	class Label : public Panel {
	protected:
		std::string m_Text;
	public:
		Label(const std::string text = "");

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		Size getPreferredSize() override;

		std::string &text() { return m_Text; }
		const std::string &text() const { return m_Text; }
	};
}