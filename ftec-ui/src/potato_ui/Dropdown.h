#pragma once

#include "Panel.h"
#include "List.h"

namespace potato {
	class Dropdown : public Panel {
	protected:
		std::weak_ptr<List> m_List;
		std::vector<std::string> m_TextOptions;
		size_t m_SelectedIndex = 0;
	public:
		Dropdown();

		void drawSelf(ftec::Graphics2D &graphics) override;
		void onClick(Event &event) override;
		Size getPreferredSize() override;

		void setTextOptions(const std::vector<std::string> &cp) { m_TextOptions = cp; }
		std::vector<std::string> &getTextOptions() { return m_TextOptions; };
		const std::vector<std::string> &getTextOptions() const { return m_TextOptions; }
	};
}