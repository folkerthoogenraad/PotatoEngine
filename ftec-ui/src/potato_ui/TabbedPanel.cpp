#include "TabbedPanel.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "engine/Input.h"

#include "math/math.h"

namespace potato {

	const int TAB_HEIGHT = 32;
	const int TAB_WIDTH = 128;

	TabbedPanel::TabbedPanel(const std::vector<std::pair<std::string, std::shared_ptr<Panel>>> &tabs) : m_SelectedTab(0)
	{
		m_Insets = { 2,2,2,2 };
		
		for (auto &pair : tabs) {
			m_TabTitles.push_back(pair.first);

			m_Children.push_back(pair.second);
			initChild(pair.second);
		}
	}

	void TabbedPanel::updateLayout()
	{
		const int offset = 4;

		if (m_SelectedTab < m_Children.size()) {
			Size layoutSize = getInnerBounds().size;
			m_Children[m_SelectedTab]->localbounds() = Bounds(
				0, TAB_HEIGHT + offset, layoutSize.width, layoutSize.height - TAB_HEIGHT - offset
			);
			m_Children[m_SelectedTab]->updateLayout();
		}
	}

	void TabbedPanel::addTab(const std::string & name, std::shared_ptr<Panel> panel)
	{
		m_TabTitles.push_back(name);
		m_Children.push_back(panel);

		initChild(panel);

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
		Bounds outline = getGlobalOutline();
		outline.height() = TAB_HEIGHT + m_Insets.top;

		Bounds bounds = getGlobalBounds();
		int offset = TAB_WIDTH / 2;
		const float lineWidth = 1;

		graphics.setColor(ftec::Color32::ltgray());
		graphics.drawRectangle(outline, true);

		graphics.setHorizontalAlign(ftec::FontAlign::CENTER);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.setLineWidth(lineWidth);

		size_t idx = 0;
		for (auto &tab : m_Children) {
			
			if (idx == m_SelectedTab) {
				Bounds rect = Bounds(
					bounds.x() + offset - TAB_WIDTH / 2,
					bounds.y(),
					TAB_WIDTH,
					TAB_HEIGHT
				);
				graphics.setColor(PotatoColor::darkPrimary);
				graphics.drawRectangle(rect, true);

				//Draw the line
				/*graphics.setColor(ftec::Color32::gray());
				graphics.drawLine(ftec::Line2f(rect.bottomleft(), rect.topleft()));
				graphics.drawLine(ftec::Line2f(rect.topleft(), rect.topright()));
				graphics.drawLine(ftec::Line2f(rect.topright(), rect.bottomright()));*/
			}
			else {
				graphics.setColor(PotatoColor::darkPrimary);
				graphics.drawLine(ftec::Line2f(
					ftec::Vector2f(bounds.x() + offset - TAB_WIDTH / 2, bounds.y() + TAB_HEIGHT - lineWidth / 2),
					ftec::Vector2f(bounds.x() + offset + TAB_WIDTH / 2, bounds.y() + TAB_HEIGHT - lineWidth / 2)
				));
			}

			if (idx != m_SelectedTab)
				graphics.setColor(PotatoColor::primaryText);
			else
				graphics.setColor(ftec::Color32::white());

			graphics.drawString(m_TabTitles[idx], ftec::Vector2f(
				(float)bounds.x()
				+ (float)offset,
				(float)bounds.y()
				+ (float)TAB_HEIGHT / 2.0f));
			offset += TAB_WIDTH;

			idx++;
		}

		graphics.setColor(PotatoColor::darkPrimary);
		graphics.drawLine(ftec::Line2f(
			ftec::Vector2f(bounds.x() + offset - TAB_WIDTH / 2, bounds.y() + TAB_HEIGHT - lineWidth / 2),
			bounds.topright() + ftec::Vector2f(0, TAB_HEIGHT - lineWidth / 2)
		));
	}

	void TabbedPanel::onClick(Event & evt)
	{
		Bounds bounds = getGlobalOutline();//TODO


		float res = (ftec::Input::getMouseX() - bounds.x()) / TAB_WIDTH;
		if (res < m_Children.size() && res > 0) {
			size_t selected = ftec::clamp(0, (int)m_Children.size() - 1, (int)ftec::floor(res));
			if (m_SelectedTab != selected) {
				// All these m_UI tests should not even have to exist.
				if (m_UI && isChildFocused()) {
					m_UI->resetFocus(evt);
				}

				m_SelectedTab = selected;

				requestUpdateLayout();
			}
		}
		evt.consume();
	}

	std::vector<std::shared_ptr<Panel>> TabbedPanel::getChildren() const
	{
		if (m_Children.size() == 0)
			return m_Children;

		//List with only one element.
		return{ m_Children[m_SelectedTab] };
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