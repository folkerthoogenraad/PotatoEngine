#include "SceneView.h"
#include "graphics/Graphics.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "engine/Engine.h"

namespace potato {
	SceneView::SceneView()
	{
		m_Focusable = true;
	}

	void SceneView::drawSelf(ftec::Graphics2D & graphics)
	{
		//Draw the scene!
		if (ftec::Engine::getScene()) {
			graphics.begin3D(m_Bounds);
			ftec::Engine::getScene()->render();
			graphics.end3D();
		}
		else {
			graphics.setColor(ftec::color32::blue());
			graphics.drawRectangle(m_Bounds, true);
			graphics.setColor(ftec::color32::white());
			graphics.setVerticalAlign(ftec::FontAlign::TOP);
			graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
			graphics.drawString("Scene missing.", m_Bounds.position + ftec::vec2i(2,2));
		}
	}

	void SceneView::update()
	{
		Panel::update();

		if (m_Focus) {
			if (ftec::Engine::getScene()) {
				ftec::Engine::getScene()->update();
			}
		}
	}
}
