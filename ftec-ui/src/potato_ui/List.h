#pragma once

#include "Panel.h"
#include <functional>

namespace potato {
	//TODO generic class, with T, with layout that stacks them on top of each other
	class List : public Panel {
	protected:
		std::vector<std::string> m_TextOptions;
		std::function<void(int)> m_Callback;
		int m_SelectedIndex = -1;
	public:
		List();

		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		Size getPreferredSize() override;

		void onHoverOrDrag(Event &event) override;
		void onHoverLeave(Event &event) override;
		void onClick(Event &event) override;

		void setSelectionCallback(std::function<void(int)> function);

		void setTextOptions(const std::vector<std::string> &cp) { m_TextOptions = cp; }
		std::vector<std::string> &getTextOptions() { return m_TextOptions; };
		const std::vector<std::string> &getTextOptions() const { return m_TextOptions; }
	};
}