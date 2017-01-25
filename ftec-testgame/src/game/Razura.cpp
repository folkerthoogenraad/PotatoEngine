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

		std::vector<Vector3r> v = {
			Vector3r(0,0,0),
			Vector3r(0,1,0),
			Vector3r(1,0,0),
			Vector3r(1,1,0),

			Vector3r(0,0,1),
			Vector3r(0,1,1),
			Vector3r(1,0,1),
			Vector3r(1,1,1)
		};

		v.push_back(Vector3r(1, 1, 1));
		v.push_back(Vector3r(2, 1, 1));
		v.push_back(Vector3r(2, 2, 1));

		scene->addEntity(std::make_unique<RationalPointCloudEntity>(v));

		Engine::setScene(std::move(scene));
	}

	void Razura::destroy()
	{ }
}
