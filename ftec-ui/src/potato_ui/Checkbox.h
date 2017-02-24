#pragma once

#include "Panel.h"

namespace potato {
	class Checkbox : public Panel {
	protected:
		bool m_Checked;
		std::string m_Text;
	public:
		Checkbox();

		void drawSelf(ftec::Graphics2D &graphics) override;
		void onClick(Event &event) override;
		Size getPreferredSize() override;

		inline bool isChecked() { return m_Checked; };
		inline void setChecked(bool c) { m_Checked = c; };

		std::string &text() { return m_Text; }
		const std::string &text() const { return m_Text; }
	};
}