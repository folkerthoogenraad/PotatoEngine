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
#include "graphics/Mesh.h"
#include "graphics/Graphics.h"

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

#include "razura/RazuraPlayer.h"

#include "TestCanvas.h"

namespace ftec {

	void Razura::update()
	{
	}

	void Razura::render()
	{
		Renderer::clear();
	}

	void Razura::init()
	{
		{
			auto scene = std::make_unique<Scene>();
			scene->setMode(Scene::SceneMode::GRAPHICS_2D);

			scene->m_Cameras[0] = Camera::orthagonal(10, 16.0f / 9.0f, -100, 100, false);

			scene->addEntity(std::make_unique<RazuraPlayer>());

			Engine::setScene(std::move(scene));
		}
	}

	void Razura::destroy()
	{ }
}
