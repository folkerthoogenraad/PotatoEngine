#include "SceneView.h"
#include "graphics/Graphics.h"
#include "graphics/Graphics2D.h"
#include "engine/Engine.h"

namespace potato {
	SceneView::SceneView()
	{
		m_Focusable = true;
	}

	void SceneView::draw(ftec::Graphics2D & graphics)
	{
		//Draw the scene!
		graphics.begin3D(m_Bounds);
		ftec::Engine::getScene()->render();
		graphics.end3D();

		Panel::draw(graphics);
	}

	void SceneView::update()
	{
		Panel::update();
		if (m_Focus) {
			ftec::Engine::getScene()->update();
		}
	}
}
