#include "TestCanvas.h"

#include "math/Matrix3.h"

#include "engine/Time.h"

#include "logger/log.h"

#include "math/math.h"

namespace ftec {


	TestCanvas::TestCanvas()
	{
		m_Focusable = true;
	}

	void TestCanvas::onPreEvents()
	{
		m_Typed = false;
		m_Clicked = false;
	}

	void TestCanvas::drawSelf(Graphics2D & graphics)
	{
		graphics.setColor(Color32::red());

		if (m_Typed)
			graphics.setColor(Color32::green());
		if (m_Clicked)
			graphics.setColor(Color32::blue());

		graphics.drawRectangle(localbounds(), true);

		graphics.setColor(Color32::white());
		graphics.drawRectangle(Rectanglef::centered(m_Position.x, m_Position.y, 16, 16), true);
	}

	void TestCanvas::onClick(potato::Event & evt)
	{
		m_Clicked = true;
	}

	void TestCanvas::onHoverEnter(potato::Event & evt)
	{
	}

	void TestCanvas::onHoverLeave(potato::Event & evt)
	{
	}

	void TestCanvas::onHover(potato::Event & evt)
	{
	}

	void TestCanvas::onDrag(potato::Event & evt)
	{
		m_Position = evt.getMousePosition();
		m_Position.x = clamp((float)localbounds().left(), (float)localbounds().right(), m_Position.x);
		m_Position.y = clamp((float)localbounds().top(), (float)localbounds().bottom(), m_Position.y);
	}

	void TestCanvas::onHoverOrDrag(potato::Event & evt)
	{
	}

	void TestCanvas::onMouseReleased(potato::Event & evt)
	{
	}

	void TestCanvas::onMousePressed(potato::Event & evt)
	{
	}

	void TestCanvas::onKeyTyped(potato::Event & evt)
	{
		m_Typed = true;
	}

	void TestCanvas::onKeyPressed(potato::Event & evt)
	{
	}

	void TestCanvas::onKeyReleased(potato::Event & evt)
	{
	}

}