#include "Razura.h"
#include "scene/Scene.h"
#include "engine/Engine.h"
#include "engine/Input.h"
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
		Input::setCursorMode(CURSOR_GRABBED);

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		scene->m_Camera.m_Position.y += 1.7f;

		Engine::setScene(scene);

		auto texture = Engine::getResourceManager().load<Texture>("textures/color_pallet.png");
		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");

		auto rock = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/rocks/rock1.obj");
		auto tree = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/trees/tree1.obj");
		auto ground = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/ground/ground1.obj");

		scene->addMesh(vec3(0, 0, 0), ground, Material(texture, shader));
		scene->addMesh(vec3(2, 0, 2), tree, Material(texture, shader));
		scene->addMesh(vec3(1, 0, 0), rock, Material(texture, shader));
		scene->addMesh(vec3(1, 0, 2), rock, Material(texture, shader));
		scene->addMesh(vec3(2, 0, 1), rock, Material(texture, shader));

		scene->addEntity(std::make_shared<NoClipCameraEntity>());

	}

	void Razura::destroy()
	{

	}
}
