#include "Razura.h"
#include "scene/Scene.h"
#include "engine/Engine.h"
#include "engine/Input.h"
#include "NoClipCameraEntity.h"
#include "graphics/Graphics.h"

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

		scene->m_Light.m_Direction = vec3f(-0.5f, -1, -0.5f).normalize();
		scene->m_Light.setShadowsEnabled(true);

		float resolutionIncrease = 1.f;
		scene->m_Camera.m_RenderTarget = std::make_shared<RenderBuffer>((int) (Engine::getWindow().getWidth() * resolutionIncrease), (int) (Engine::getWindow().getHeight() * resolutionIncrease));

		Engine::setScene(scene);

		auto texture = Engine::getResourceManager().load<Texture>("textures/color_pallet.png");
		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");

		auto ground = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/ground/ground1.obj");
		auto tree = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/trees/tree1.obj");
		auto building = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/buildings/urban_building1.obj");

		scene->addMesh(vec3f(0, 0, 0), ground, Material(texture, shader));

		scene->addMesh(vec3f(0, 0, 2), tree, Material(texture, shader));
		scene->addMesh(vec3f(7, 0, 1), tree, Material(texture, shader));
		scene->addMesh(vec3f(-7, 0, 2), tree, Material(texture, shader));

		scene->addMesh(vec3f(0, 0, -6), building, Material(texture, shader));
		scene->addMesh(vec3f(-7, 0, -6), building, Material(texture, shader));
		scene->addMesh(vec3f(7, 0, -6), building, Material(texture, shader));

		scene->addEntity(std::make_shared<NoClipCameraEntity>());

	}

	void Razura::destroy()
	{

	}
}
