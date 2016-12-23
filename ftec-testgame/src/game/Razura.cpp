#include "Razura.h"

#include "engine/Engine.h"

#include "scene/Scene.h"

#include "graphics/Renderer.h"
#include "graphics/Window.h"
#include "graphics/Camera.h"

#include "razura/RazuraPlayer.h"
#include "razura/RazuraWorldEntity.h" //RazuraWorld?

#include "NoClipCameraEntity.h"

namespace ftec {

	void Razura::update()
	{ }

	void Razura::render()
	{
		Renderer::clear();
	}
	void Razura::init()
	{
		auto scene = std::make_unique<Scene>();
		scene->setMode(Scene::GRAPHICS_3D);

		scene->m_Cameras[0] = Camera::perspective(60, Engine::getWindow().getAspectRatio(), 0.01f, 100.0f);

		scene->addEntity(std::make_unique<NoClipCameraEntity>());
		scene->addEntity(std::make_unique<RazuraPlayer>());
		scene->addEntity(std::make_unique<RazuraWorldEntity>());

		Engine::setScene(std::move(scene));
	}

	void Razura::destroy()
	{ }
}
