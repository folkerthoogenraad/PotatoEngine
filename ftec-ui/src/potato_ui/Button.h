#pragma once

#include "Panel.h"

namespace potato {
	class Button : public Panel{
	protected:
		std::string m_Text;
	public:
		Button(std::shared_ptr<ftec::EngineContext> context, const std::string &text = "");

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		Size getPreferredSize() override;

		void onMousePressed(ftec::Event &event) override { repaint(); }
		void onMouseReleased(ftec::Event &event) override { repaint(); }

		std::string &text() { return m_Text; }
		const std::string &text() const { return m_Text; }
	};
}