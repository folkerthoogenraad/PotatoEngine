#include "Dropdown.h"
#include "graphics/Font.h"
#include "logger/log.h"

namespace potato {

	Dropdown::Dropdown()
	{
		m_Focusable = true;
	}

	void Dropdown::drawSelf(ftec::Graphics2D & graphics)
	{
		Panel::drawSelf(graphics);

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

	void Dropdown::onClick(Event &event)
	{
		Bounds bounds = getGlobalBounds();

		//Get reference to the ui, if that failes, we can't make the popup
		if (m_UI) {
			if (m_List.expired()) {
				auto list = std::make_shared<List>();
				list->setTextOptions(m_TextOptions);

				list->localbounds() = ftec::Rectanglei(bounds.left(), bounds.bottom(), bounds.width(), 64);

				m_UI->setContextMenu(list);
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
}
