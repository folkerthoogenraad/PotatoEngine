#include "Razura.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

#include "scene/Scene.h"

#include "math/Matrix4.h"

#include "graphics/Renderer.h"
#include "graphics/Window.h"
#include "graphics/Camera.h"

#include "razura/RazuraPlayer.h"
#include "razura/RazuraWorldEntity.h"

#include "potato_ui/PotatoUI.h"
#include "potato_ui/Button.h"
#include "potato_ui/LinearLayout.h"

#include "NoClipCameraEntity.h"

namespace ftec {

	void Razura::update()
	{ 
		if (m_UI)
			m_UI->update();
	}

	void Razura::render()
	{
		Renderer::clear();

		if (m_UI)
			m_UI->render();
	}

	void Razura::init()
	{
		m_UI = std::make_shared<potato::PotatoUI>();
		auto layout = std::make_shared<potato::LinearLayout>(potato::LinearLayout::VERTICAL);
		
		layout->addPanel(std::make_shared<potato::Button>("test123"));
		layout->addPanel(std::make_shared<potato::Button>("Hello wrold"));
		layout->addPanel(std::make_shared<potato::Button>("dikke stuff"));

		m_UI->setRoot(
			layout
		);
	}

	void Razura::destroy()
	{ }
}
