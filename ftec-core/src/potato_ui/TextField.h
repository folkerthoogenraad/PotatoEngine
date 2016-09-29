#pragma once

#include "Panel.h"

namespace potato {
	class TextField : public Panel {
	protected:
		std::string m_Text;
		std::string m_Hint;
		size_t m_CursorPosition;
	public:
		TextField();

		void update() override;
		void draw(ftec::Graphics2D &graphics) override;

		std::string &text() { return m_Text; }
		const std::string &text() const { return m_Text; }

		std::string &hint() { return m_Hint; }
		const std::string &hint() const { return m_Hint; }
	};
}