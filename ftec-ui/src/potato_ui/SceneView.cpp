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
		Bounds bounds = getGlobalBounds();
		//Draw the scene!
		if (ftec::Engine::getScene()) {
			graphics.begin3D(bounds);
			ftec::Engine::getScene()->render();
			graphics.end3D();
		}
		else {
			graphics.setColor(ftec::color32::blue());
			graphics.drawRectangle(bounds, true);
			graphics.setColor(ftec::color32::white());
			graphics.setVerticalAlign(ftec::FontAlign::TOP);
			graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
			graphics.drawString("Scene missing.", bounds.position + ftec::vec2i(2,2));
		}
	}

	void SceneView::update()
	{
		Panel::update();

		//TODO maybe synchronize this with other sceneviews? 
		if (!m_Focus) //TODO make a safe object that has a destructor that re-enables the input, thats just more safe
			ftec::Input::setEnabled(false);
		
		if (ftec::Engine::getScene()) {
			ftec::Engine::getScene()->update();
		}

		if (!m_Focus)
			ftec::Input::setEnabled(true);
	}
	Size SceneView::getPreferredSize()
	{
		//TODO change these accordingly
		return Size(128,72);
	}
}
