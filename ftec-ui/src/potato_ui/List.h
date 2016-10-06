#pragma once

#include "Panel.h"

namespace potato {
	//TODO generic class, with T, with layout that stacks them on top of each other
	class List : public Panel {
	protected:
		std::vector<std::string> m_TextOptions;
	public:
		List();

		void drawSelf(ftec::Graphics2D &graphics) override;
		void processSelf(Event &event) override;
		Size getPreferredSize() override;

		void setTextOptions(const std::vector<std::string> &cp) { m_TextOptions = cp; }
		std::vector<std::string> &getTextOptions() { return m_TextOptions; };
		const std::vector<std::string> &getTextOptions() const { return m_TextOptions; }
	};
}