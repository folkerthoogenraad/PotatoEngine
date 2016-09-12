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
		Engine::setScene(scene);

		auto texture = Engine::getResourceManager().load<Texture>("textures/wheelchair_texture.png");
		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");
		auto mesh = Engine::getResourceManager().load<Mesh>("mesh/test.obj");

		scene->addMesh(vec3(0,0,-3), mesh, Material(texture, shader));

		scene->addEntity(std::make_shared<NoClipCameraEntity>());

	}

	void Razura::destroy()
	{

	}
}
