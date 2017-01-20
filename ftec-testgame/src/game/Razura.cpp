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
#include "potato_ui/Slider.h"
#include "potato_ui/TextField.h"

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

		auto b = std::make_shared<potato::Button>("abcdefghijklmn");
		b->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;
		auto b2 = std::make_shared<potato::Button>("more stuff");
		b2->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;

		auto tf = std::make_shared<potato::TextField>();
		tf->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;
		tf->layoutparams().m_Weight = 2.0f;
		tf->hint() = "test text";

		layout->addPanel(b);
		layout->addPanel(std::make_shared<potato::Button>("Hello world"));
		layout->addPanel(std::make_shared<potato::Button>("abcdefghijklmn"));
		layout->addPanel(b2);
		layout->addPanel(tf);

		m_UI->setRoot(
			layout
		);
	}

	void Razura::destroy()
	{ }
}
