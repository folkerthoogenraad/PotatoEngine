#pragma once

#include "Panel.h"

namespace potato {
	class Checkbox : public Panel {
	protected:
		bool m_Checked;
		std::string m_Text;
	public:
		Checkbox(std::shared_ptr<ftec::EngineContext> context);

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		void onClick(ftec::Event &event) override;
		Size getPreferredSize() override;

		inline bool isChecked() { return m_Checked; };
		inline void setChecked(bool c) { m_Checked = c; repaint(); };

		std::string &text() { return m_Text; }
		const std::string &text() const { return m_Text; }
	};
}