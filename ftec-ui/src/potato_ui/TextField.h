#pragma once

#include "Panel.h"
#include "EditText.h"

namespace potato {
	class TextField : public Panel {
	protected:
		std::string m_Hint;
		EditText m_EditText;
	public:
		TextField(std::shared_ptr<ftec::EngineContext> context);

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;

		void onFocusGain(ftec::Event &event) override;
		void onFocusLose(ftec::Event &event) override;
		void onKeyTyped(ftec::Event &event) override;
		void onKeyPressed(ftec::Event &event) override;

		EditText &text() { return m_EditText; }
		const EditText &text() const { return m_EditText; }

		std::string &hint() { return m_Hint; }
		const std::string &hint() const { return m_Hint; }

		Size getPreferredSize() override;
	};
}