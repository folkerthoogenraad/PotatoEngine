#include "Razura.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

#include "scene/Scene.h"

#include "math/Matrix4.h"

#include "graphics/Renderer.h"
#include "graphics/Window.h"
#include "graphics/Camera.h"

#include "NoClipCameraEntity.h"

#include "RationalPointCloudEntity.h"
#include "BSPEntity.h"

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
		auto scene = std::make_unique<Scene>();

		scene->addEntity(std::make_unique<NoClipCameraEntity>());

		scene->addEntity(std::make_unique<BSPEntity>());

		Engine::setScene(std::move(scene));
	}

	void Razura::destroy()
	{ }
}
