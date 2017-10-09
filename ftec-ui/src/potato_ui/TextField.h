#pragma once

#include "Panel.h"
#include "EditText.h"

namespace potato {
	class TextField : public Panel {
	protected:
		std::string m_Hint;
		EditText m_EditText;
	public:
		TextField();

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;

		void onKeyTyped(Event &event) override;

		EditText &text() { return m_EditText; }
		const EditText &text() const { return m_EditText; }

		std::string &hint() { return m_Hint; }
		const std::string &hint() const { return m_Hint; }

		Size getPreferredSize() override;
	};
}