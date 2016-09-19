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

	std::shared_ptr<Light> light;
	void Razura::render()
	{
		Graphics::enqueueLight(light.get());
	}

	void Razura::init()
	{
		Input::setCursorMode(CURSOR_GRABBED);

		light = std::make_shared<Light>();

		light->m_Direction = vec3(-0.5f, -1, -0.5f).normalize();
		light->setShadowsEnabled(true);

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		scene->m_Camera.m_Position.y += 1.7f;

		float resolutionIncrease = 1.f;
		scene->m_Camera.m_RenderTarget = std::make_shared<RenderBuffer>((int) (Engine::getWindow().getWidth() * resolutionIncrease), (int) (Engine::getWindow().getHeight() * resolutionIncrease));
		scene->m_Camera.m_PostProcessingShader = Engine::getResourceManager().load<Shader>("shaders/post");

		Engine::setScene(scene);

		auto texture = Engine::getResourceManager().load<Texture>("textures/color_pallet.png");
		auto white = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");

		auto rock = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/rocks/rock1.obj");
		auto tree = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/trees/tree1.obj");
		auto ground = Engine::getResourceManager().load<Mesh>("mesh/lowpoly/environment/ground/ground1.obj");
		auto test3 = Engine::getResourceManager().load<Mesh>("mesh/test3.obj");
		auto ape = Engine::getResourceManager().load<Mesh>("mesh/ape.obj");

		scene->addMesh(vec3(0, 0, 0), ground, Material(texture, shader));
		scene->addMesh(vec3(2, 0, 2), tree, Material(texture, shader));

		scene->addMesh(vec3(4, 2, 4), rock, Material(texture, shader));
		scene->addMesh(vec3(-2, 0, -2), ape, Material(white, shader));
		scene->addMesh(vec3(2, 0, -2), test3, Material(white, shader));

		scene->addEntity(std::make_shared<NoClipCameraEntity>());

	}

	void Razura::destroy()
	{

	}
}
