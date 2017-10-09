#include "Dropdown.h"
#include "graphics/Font.h"
#include "logger/log.h"
#include "ContextMenuPanel.h"

namespace potato {

	Dropdown::Dropdown()
	{
		m_Focusable = true;
	}

	void Dropdown::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Panel::drawSelf(graphics, style);

		Bounds bounds = getGlobalBounds();

		if (isFocused()) {//Make this a function (draw focus box, or something)
			graphics.setColor(PotatoColor::darkPrimary);
			graphics.drawRectangle(bounds, false);
		}
		else {
			graphics.setColor(PotatoColor::lightPrimary);
			graphics.drawRectangle(bounds, false);
		}

		if (m_SelectedIndex < m_TextOptions.size()) {
			graphics.setColor(PotatoColor::primaryText);
			graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
			graphics.setVerticalAlign(ftec::FontAlign::CENTER);
			graphics.drawString(m_TextOptions[m_SelectedIndex], bounds.centerLeft());
		}

		graphics.setColor(PotatoColor::primary);
		graphics.drawRectangle(ftec::Rectanglef(
			(float) bounds.centerRight().x - 18,
			(float) bounds.centerRight().y - 8,
			16,16
		), true);
	}

	void Dropdown::onClick(Event &even)
	{
		Bounds bounds = getGlobalBounds();

		//Get reference to the ui, if that failes, we can't make the popup
		if (m_UI) {
			if (m_List.expired()) {
				auto list = std::make_shared<List>();
				list->setTextOptions(m_TextOptions);

				list->localbounds() = ftec::Rectanglei(bounds.left(), bounds.bottom(), bounds.width(), list->getPreferredSize().height);

				list->setSelectionCallback(std::bind(&Dropdown::setSelectedIndex, this, std::placeholders::_1));

				m_UI->setContextMenu(std::make_shared<ContextMenuPanel>(list));
			}
			else {
				m_UI->setContextMenu(nullptr);
			}

		}
		
	}
	Size Dropdown::getPreferredSize()
	{
		//TODO change these values accordingly
		return Size(128,32);
	}

	void Dropdown::setSelectedIndex(int i)
	{
		m_SelectedIndex = i;
	}
}
