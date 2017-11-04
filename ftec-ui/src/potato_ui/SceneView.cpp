#include "SceneView.h"
#include "graphics/Graphics.h"
#include "graphics/Graphics2D.h"
#include "graphics/Font.h"
#include "engine/Engine.h"
#include "engine/Input.h"
#include "scene/Scene.h"

namespace potato {
	SceneView::SceneView(std::shared_ptr<ftec::EngineContext> context)
		: Panel(context)
	{
		m_Focusable = true;
	}

	void SceneView::drawSelf(ftec::Graphics2D & graphics, const PotatoStyle& style)
	{
		Bounds bounds = getGlobalBounds();
		
		// TODO fix the sceneview component!
		
		//Draw the scene!
		//if (ftec::Engine::getScene()) {
		//	graphics.begin3D(bounds);
		//	ftec::Engine::getScene()->render();
		//	graphics.end3D();
		//}
		//else {
		{
			graphics.setColor(ftec::Color32::blue());
			graphics.drawRectangle(bounds, true);
			graphics.setColor(ftec::Color32::white());
			graphics.setVerticalAlign(ftec::FontAlign::TOP);
			graphics.setHorizontalAlign(ftec::FontAlign::LEFT);
			graphics.drawString("Scene missing.", bounds.position + ftec::Vector2i(2,2));
		}
	}

	void SceneView::update()
	{
		Panel::update();

		repaint();

		//TODO maybe synchronize this with other sceneviews? 
		if (!isFocused()) //TODO make a safe object that has a destructor that re-enables the input, thats just more safe
			m_Context->getInput().setEnabled(false);
		
		//TODO fucking fix this.

		//if (ftec::Engine::getScene()) {
		//	ftec::Engine::getScene()->update();
		//}

		if (!isFocused())
			m_Context->getInput().setEnabled(true);
	}
	Size SceneView::getPreferredSize()
	{
		//TODO change these accordingly
		return Size(128,72);
	}
}
