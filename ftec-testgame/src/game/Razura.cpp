#include "Razura.h"

#include "engine/Engine.h"
#include "engine/Input.h"
#include "logger/log.h"
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

#include "potato_ui/Event.h"
#include "potato_ui/EventInput.h"

#include "TestCanvas.h"

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
		/*{
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
			layout->addPanel(std::make_shared<TestCanvas>());

			m_UI->setRoot(
				layout
			);
		}*/

		{
			auto scene = std::make_unique<Scene>();
			scene->setMode(Scene::SceneMode::GRAPHICS_BOTH);

			scene->m_Cameras[0] = Camera::orthagonal(10, 16.0f / 9.0f, -100, 100, false);
			scene->m_Cameras[0].m_Yaw = 45.0f;
			scene->m_Cameras[0].m_Pitch = 45.0f / 2.0f;

			LOG(scene->m_Cameras[0].getViewMatrix());

			scene->addEntity(std::make_unique<NoClipCameraEntity>());

			Engine::setScene(std::move(scene));
		}
	}

	void Razura::destroy()
	{ }
}
