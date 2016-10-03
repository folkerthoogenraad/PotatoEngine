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


	bool grabbed = false;

	void Razura::update()
	{
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
			grabbed = !grabbed;
			Input::setCursorMode(grabbed ? CURSOR_GRABBED : CURSOR_NORMAL);//TODO make an enum out of this
		}
		panel.update();
		Engine::getScene()->update();
	}


	std::shared_ptr<Light> light;

	void Razura::render()
	{
		Renderer::clear();

		Graphics::begin();

		Graphics::enqueueLight(light.get());

		Engine::getScene()->render();

		Graphics::end();

		graphics.resetClip();

		graphics.begin();

		panel.draw(graphics);

		graphics.end();

		
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

		light = std::make_shared<Light>();

		light->m_Direction = vec3f(-0.5f, -1, -0.5f).normalize();

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		scene->m_Camera.m_Position.y += 1.7f;

		float resolutionIncrease = 1.f;
		
		Engine::setScene(scene);

		auto wood = Engine::getResourceManager().load<Texture>("textures/wood.jpg");
		auto woodNormal = Engine::getResourceManager().load<Texture>("textures/wood_normal.jpg");

		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");
		auto sphere = Engine::getResourceManager().load<Mesh>("mesh/sphere.obj");
		auto ground = Engine::getResourceManager().load<Mesh>("mesh/plane.obj");

		Material mat(wood, shader);
		mat.m_TextureMap = wood;
		mat.m_NormalMap = woodNormal;

		scene->addMesh(vec3f(0, 1, 0), sphere, mat);
		scene->addMesh(vec3f(0, 0, 0), ground, mat);

		scene->addEntity(std::make_shared<NoClipCameraEntity>());
	}

	void Razura::destroy()
	{

	}
}
