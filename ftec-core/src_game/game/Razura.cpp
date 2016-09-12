#include "Razura.h"
#include "scene/Scene.h"
#include "engine/Engine.h"
#include "NoClipCameraEntity.h"

namespace ftec {
	Razura::Razura()
	{

	}

	Razura::~Razura()
	{

	}

	void Razura::update()
	{

	}
	void Razura::render()
	{

	}

	void Razura::init()
	{
		std::shared_ptr<Scene> scene = std::make_shared<Scene>();

		scene->addEntity(std::make_shared<NoClipCameraEntity>());

		Engine::setScene(scene);
	}

	void Razura::destroy()
	{

	}
}
