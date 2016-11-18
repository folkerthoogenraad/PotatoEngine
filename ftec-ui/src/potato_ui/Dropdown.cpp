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

		if (m_Focus) {//Make this a function (draw focus box, or something)
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
		graphics.drawRectangle(ftec::rectf(
			bounds.centerRight().x - 18,
			bounds.centerRight().y - 8,
			16,16
		), true);
	}

	void Dropdown::onClick()
	{
		Bounds bounds = getGlobalBounds();

		//Get reference to the ui, if that failes, we can't make the popup
		if (auto ui = m_UI.lock()) {
			if (m_List.expired()) {
				auto list = std::make_shared<List>();
				list->setTextOptions(m_TextOptions);

				list->localbounds() = ftec::recti(bounds.left(), bounds.bottom(), bounds.width(), 64);

				ui->setContextMenu(list);
			}
			else {
				ui->setContextMenu(nullptr);
			}

		}
		
	}
	Size Dropdown::getPreferredSize()
	{
		//TODO change these values accordingly
		return Size(128,32);
	}
}
