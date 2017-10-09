#pragma once

#include "Panel.h"
#include <vector>

namespace potato {
	//TODO add direction for this
	//TODO bugfix that you can add panels to this for no reason
	class TabbedPanel : public Panel{

		size_t m_SelectedTab;
		std::vector<std::string> m_TabTitles;

	public:
		TabbedPanel(const std::vector<std::pair<std::string, std::shared_ptr<Panel>>> &tabs = {});

		void updateLayout() override;
		void addTab(const std::string &name, std::shared_ptr<Panel> panel);

		void update() override;
		void draw(ftec::Graphics2D &graphics, const PotatoStyle &style) override;
		void drawSelf(ftec::Graphics2D &graphics, const PotatoStyle &style) override;

		void onClick(Event &evt);

		void setUI(PotatoUI *ui);
		std::vector<std::shared_ptr<Panel>> getChildren() const override;

		Size getPreferredSize() override;
	};
}