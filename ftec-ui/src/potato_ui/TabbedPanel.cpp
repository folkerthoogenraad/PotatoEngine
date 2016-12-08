#include "TabbedPanel.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "engine/Input.h"

namespace potato {

	const int TAB_HEIGHT = 32;
	const int TAB_WIDTH = 128;

	TabbedPanel::TabbedPanel(const std::vector<std::pair<std::string, std::shared_ptr<Panel>>> &tabs) : m_SelectedTab(0)
	{
		m_Insets = { 0,0,0,0 };
		
		for (auto &pair : tabs) {
			m_TabTitles.push_back(pair.first);
			m_Children.push_back(pair.second);
		}
	}

	void TabbedPanel::updateLayout()
	{
		if (m_SelectedTab < m_Children.size()) {
			Size layoutSize = localbounds().size;
			m_Children[m_SelectedTab]->localbounds() = Bounds(
				0, TAB_HEIGHT, layoutSize.width, layoutSize.height - TAB_HEIGHT
			);
			m_Children[m_SelectedTab]->updateLayout();
		}
	}

	void TabbedPanel::addTab(const std::string & name, std::shared_ptr<Panel> panel)
	{
		m_TabTitles.push_back(name);
		m_Children.push_back(panel);

		requestUpdateLayout();
	}

	void TabbedPanel::update()
	{
		if (m_SelectedTab < m_Children.size()) {
			m_Children[m_SelectedTab]->update();
		}
	}

	void TabbedPanel::draw(ftec::Graphics2D & graphics)
	{
		if (m_SelectedTab < m_Children.size()) {
			m_Children[m_SelectedTab]->draw(graphics);
		}
		drawSelf(graphics);
	}

	void TabbedPanel::drawSelf(ftec::Graphics2D & graphics)
	{
		Bounds bounds = getGlobalBounds();
		int offset = TAB_WIDTH / 2;

		graphics.setHorizontalAlign(ftec::FontAlign::CENTER);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);

		size_t idx = 0;
		for (auto &tab : m_Children) {
			
			if (idx == m_SelectedTab) {
				graphics.setColor(PotatoColor::lightPrimary);
				graphics.drawRectangle(Bounds(
					bounds.x() + offset - TAB_WIDTH / 2,
					bounds.y(),
					TAB_WIDTH,
					TAB_HEIGHT
				), true);

			}
			graphics.setColor(PotatoColor::primaryText);
			graphics.drawString(m_TabTitles[idx], ftec::vec2f(
				(float)bounds.x()
				+ (float)offset,
				(float)bounds.y()
				+ (float)TAB_HEIGHT / 2.0f));
			offset += TAB_WIDTH;

			idx++;
		}
	}

	void TabbedPanel::process(Event & event)
	{
		/*for (auto &tab : m_Children) {
			if (!event.isConsumed()) {
				tab->process(event);
			}
			else {
				break;
			}
		}*/
		if (m_SelectedTab < m_Children.size()) {
			m_Children[m_SelectedTab]->process(event);
		}

		if (!event.isConsumed())
			processSelf(event);
	}

	void TabbedPanel::processSelf(Event & event)
	{
		bool m = m_Pressed;
		Panel::processSelf(event);

		//Click hack :')
		//TODO clean this up
		if (m != m_Pressed && !m_Pressed) {
			Bounds bounds = getGlobalOutline();//TODO

			float res = (ftec::Input::getMouseX() - bounds.x()) / TAB_WIDTH;
			if (res < m_Children.size() && res > 0) {
				m_SelectedTab = ftec::clamp(0, (int)m_Children.size() - 1, (int)ftec::floor(res));
				requestUpdateLayout();
			}
		}
	}

	Size TabbedPanel::getPreferredSize()
	{
		Size s(0, TAB_HEIGHT);

		for (auto &tab : m_Children) {
			s.x += TAB_WIDTH;
		}

		if (m_SelectedTab < m_Children.size()) {
			Size b = m_Children[m_SelectedTab]->getPreferredSize();
			s.y += b.y;
			s.x = ftec::max(s.x, b.x);
		}

		return s;
	}
}