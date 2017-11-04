#include "List.h"
#include "graphics/Font.h"
#include "logger/log.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"


namespace potato {
	List::List(std::shared_ptr<ftec::EngineContext> context)
		: Panel(context)
	{
		m_Opaque = false;
	}

	void List::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Panel::drawSelf(graphics, style);

		Bounds bounds = getGlobalBounds();
		Bounds outline = getGlobalOutline();

		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
		graphics.setVerticalAlign(ftec::FontAlign::CENTER);

		ftec::Color32 base = PotatoColor::lightPrimary;
		base.a = 200;

		graphics.setColor(base);
		graphics.drawRectangle(outline, true);

		float offset = 0;
		float center = 4;

		size_t idx = 0;

		for (auto &s : m_TextOptions) {
			Bounds t = bounds;
			t.height() = 16 + (int)center;

			t.y() = (int)offset + t.y();

			if (m_SelectedIndex == idx) {
				graphics.setColor(base);
				graphics.drawRectangle(t, true);
			}
			graphics.setColor(PotatoColor::primaryText);
			graphics.drawString(s, ftec::Vector2i(bounds.left(), bounds.top() + (int)offset - (int) center / 2 + (int)(t.height() / 2)));
			offset += 16.f + center;

			idx++;
		}
	}

	Size List::getPreferredSize()
	{
		return Size(128, m_Insets.top + m_Insets.bottom + (int)m_TextOptions.size() * 20);
	}

	void List::onHoverOrDrag(ftec::Event & event)
	{
		repaint();
		// Dragging can be out of the bounds
		if (!inBounds(event.getMousePosition())) {
			m_SelectedIndex = -1;
			return;
		}

		float localY = event.getMousePosition().y - getGlobalBounds().position.y - m_Insets.top;

		m_SelectedIndex = (int) (localY / 20.0f);
	}

	void List::onHoverLeave(ftec::Event & event)
	{
		m_SelectedIndex = -1;
		repaint();
	}

	void List::onClick(ftec::Event & event)
	{
		if (m_SelectedIndex >= 0)
			m_Callback(m_SelectedIndex);

		if (m_UI) {
			//This calles our destructor, which is nice :') /s
			//This can break lots of things if used incorrectly.
			//Luckally we proccess our events as last (children first)
			//If children are processed first we must find a workaroudn for this.
			//TODO do that	
			m_UI->setContextMenu(nullptr);
		}
	}

	void List::setSelectionCallback(std::function<void(int)> f)
	{
		m_Callback = f;
	}
}
