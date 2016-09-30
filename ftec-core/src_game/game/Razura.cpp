#include "Razura.h"
#include "scene/Scene.h"
#include "engine/Engine.h"
#include "engine/Input.h"
#include "NoClipCameraEntity.h"
#include "graphics/Graphics.h"

#include "graphics/GraphicsState.h"
#include "graphics/Shader.h"

#include "graphics/Graphics2D.h"
#include "math/math.h"
#include "graphics/Font.h"

#include "potato_ui/Button.h"
#include "potato_ui/TextField.h"
#include "graphics/Renderer.h"

namespace ftec {

	Razura::Razura()
		:sprite(Engine::getResourceManager().load<Texture>("textures/spritesheet.png"), rect2f(16, 0, 33, 33))
	{

	}


	void Razura::update()
	{
		panel.update();
		Engine::getScene()->update();
	}


	std::shared_ptr<Light> light;

	void Razura::render()
	{
		graphics.resetClip();
		graphics.drawClear();

		graphics.begin();

		panel.draw(graphics);

		graphics.end();

		rect2i b(512,0,1280/2, 720/2);

		Renderer::clip(b);
		Renderer::viewport(b);
		Renderer::clear();

		Graphics::begin();

		Graphics::enqueueLight(light.get());

		Engine::getScene()->render();

		Graphics::end();
	}

	void Razura::init()
	{
		auto button = std::make_shared<potato::Button>();
		auto textfield = std::make_shared<potato::TextField>();
		auto textfield2 = std::make_shared<potato::TextField>();

		button->text() = "Button Test!";
		textfield->hint() = "Username";
		textfield2->hint() = "Password";

		button->bounds() = rect2i(2, 2, 128 - 4, 32 - 4);
		textfield->bounds() = rect2i(2, 32 + 2, 512 - 4, 32 - 4);
		textfield2->bounds() = rect2i(2, 64 + 2, 512 - 4, 32 - 4);

		panel.bounds() = rect2i(0,0, 512, 256);

		panel.addPanel(button);
		panel.addPanel(textfield);
		panel.addPanel(textfield2);

		//TODO
		Input::setCursorMode(CURSOR_GRABBED);//TODO make an enum out of this

		light = std::make_shared<Light>();

		light->m_Direction = vec3f(-0.5f, -1, -0.5f).normalize();

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		scene->m_Camera.m_Position.y += 1.7f;

		float resolutionIncrease = 1.f;
		
		Engine::setScene(scene);

		auto monker = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
		auto monkey = Engine::getResourceManager().load<Mesh>("mesh/monkey.obj");
		auto sphere = Engine::getResourceManager().load<Mesh>("mesh/sphere.obj");
		auto donut = Engine::getResourceManager().load<Mesh>("mesh/donut.obj");
		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");

		scene->addMesh(vec3f(0, 0, 0), monkey, Material(monker, shader));
		scene->addMesh(vec3f(-4, 0, 0), donut, Material(monker, shader));
		scene->addMesh(vec3f(4, 0, 0), sphere, Material(monker, shader));
		/*
		auto texture = Engine::getResourceManager().load<Texture>("textures/color_pallet.png");
		
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
		*/
		scene->addEntity(std::make_shared<NoClipCameraEntity>());
	}

	void Razura::destroy()
	{

	}
}
