#include "TextField.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "engine/Input.h"
#include "PotatoUI.h"

namespace potato {
	TextField::TextField(std::shared_ptr<ftec::EngineContext> context)
		:Panel(context)
	{
		m_Focusable = true;
	}

	void TextField::onKeyTyped(ftec::Event & event)
	{
		m_EditText.keyboardInput(event);
		repaint();
	}

	void TextField::onKeyPressed(ftec::Event & event)
	{
		m_EditText.keyboardInput(event);
		repaint();
	}

	void TextField::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		//TODO manage to find a solution for this
		//graphics.setClip(getGlobalOutline());
		Bounds bounds = getGlobalBounds();

		graphics.setLineWidth(2);
		if (isFocused()) {
			graphics.setColor(style.m_AccentColor);
		}
		else {
			graphics.setColor(style.m_DarkBackground);
		}
		graphics.drawLine(bounds.bottomright(), bounds.bottomleft());

		graphics.setFont(m_Font);

		graphics.setVerticalAlign(ftec::FontAlign::CENTER);
		graphics.setHorizontalAlign(ftec::FontAlign::LEFT);

		if (m_EditText.length() == 0) {
			graphics.setColor(style.m_SecondaryColor);
			graphics.drawString(m_Hint, ftec::Vector2i(bounds.x(), bounds.center().y));
		}
		else {
			graphics.setColor(style.m_PrimaryColor);
			graphics.drawString(m_EditText.m_Text, ftec::Vector2i(bounds.x(), bounds.center().y));
		}

		ftec::Color32 color = style.m_AccentColor;

		if(isFocused())
			color.a = 0x88;
		else
			color.a = 0x33;

		graphics.setColor(color);

		auto start = m_Font->measure(m_EditText.m_Text.substr(0, m_EditText.selectionStart())).x - 1;
		auto end = m_Font->measure(m_EditText.m_Text.substr(0, m_EditText.selectionEnd())).x + 1;
		auto center = bounds.center();

		graphics.drawRectangle(
			ftec::Rectanglef(
				bounds.x() + start,
				center.y - m_Font->getSize()/2,
				end - start,
				m_Font->getSize()
			),
			true
		);

		//TODO see top of function
		//graphics.resetClip();
	}
	void TextField::onFocusGain(ftec::Event & event)
	{
		repaint();
	}
	void TextField::onFocusLose(ftec::Event & event)
	{
		repaint();
	}
	Size TextField::getPreferredSize()
	{
		//TODO change these accoringly
		return Size(128,32);
	}
}
