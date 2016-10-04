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
#include "potato_ui/SceneView.h"
#include "graphics/Renderer.h"

namespace ftec {


	bool grabbed = false;

	void Razura::update()
	{
		//This is temp code!
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
			grabbed = !grabbed;
			Input::setCursorMode(grabbed ? CURSOR_GRABBED : CURSOR_NORMAL);//TODO make an enum out of this
		}
		ui.update();
	}


	std::shared_ptr<Light> light;

	void Razura::render()
	{
		ui.render();
	}

	void Razura::init()
	{
		auto rootPanel = std::make_shared<potato::SceneView>();
		auto button = std::make_shared<potato::Button>();
		auto textfield = std::make_shared<potato::TextField>();
		auto textfield2 = std::make_shared<potato::TextField>();

		button->text() = "Button Test!";
		textfield->hint() = "Username";
		textfield2->hint() = "Password";

		button->bounds() = rect2i(2, 2, 128 - 4, 32 - 4);
		textfield->bounds() = rect2i(2, 32 + 2, 512 - 4, 32 - 4);
		textfield2->bounds() = rect2i(2, 64 + 2, 512 - 4, 32 - 4);

		rootPanel->bounds() = rect2i(0,0, 1024, 640);

		rootPanel->addPanel(button);
		rootPanel->addPanel(textfield);
		rootPanel->addPanel(textfield2);

		ui.setRoot(rootPanel);

		//TODO

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		scene->m_Light.m_Intensity = 1.5;
		scene->m_Light.m_Direction = vec3f(0.7f, -0.4f, -0.7f).normalize();
		scene->m_Camera.m_Position.y += 1.7f;

		float resolutionIncrease = 1.f;
		
		Engine::setScene(scene);

		auto tableTexture = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);

		auto tiles = Engine::getResourceManager().load<Texture>("textures/tiles2_texture.png");
		auto tilesNormal = Engine::getResourceManager().load<Texture>("textures/tiles2_normal.png");
		auto couchTexture = Engine::getResourceManager().load<Texture>("textures/couch_texture.png");
		auto couchNormal = Engine::getResourceManager().load<Texture>("textures/leather_normal.jpg");

		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");
		auto sphere = Engine::getResourceManager().load<Mesh>("mesh/sphere.obj");
		auto table = Engine::getResourceManager().load<Mesh>("mesh/table.obj");
		auto ground = Engine::getResourceManager().load<Mesh>("mesh/plane.obj");
		auto couch = Engine::getResourceManager().load<Mesh>("mesh/couch.obj");

		Material tableMat(tableTexture, shader);
		tableMat.m_Metallicness = 0.2f;
		tableMat.m_Albedo = vec3f(0.5, 0.5, 0.5);
		tableMat.m_Roughness = 0.05f;
		tableMat.m_Bumpiness = 0.0f;
		tableMat.m_Tiling = vec2f(2, 2);

		Material tilesMat(tiles, shader);
		tilesMat.m_NormalMap = tilesNormal;
		tilesMat.m_Roughness = 0.05f;
		tilesMat.m_Specular = vec3f(0.3,0.3,0.3);
		tilesMat.m_Metallicness = 0.0f;
		tilesMat.m_Bumpiness = 1.0f;
		tilesMat.m_Tiling = vec2f(4, 4);

		Material couchMat(couchTexture, shader);
		couchMat.m_NormalMap = couchNormal;
		couchMat.m_Bumpiness = 0.6f;
		couchMat.m_Roughness = 0.55f;
		couchMat.m_Tiling = vec2f(4,4);

		scene->addMesh(vec3f(1.5, 0, 0), table, tableMat);
		scene->addMesh(vec3f(0, 0, 0), ground, tilesMat);

		scene->addMesh(vec3f(0, 0.3f, -1), couch, couchMat);

		scene->addEntity(std::make_shared<NoClipCameraEntity>());
	}

	void Razura::destroy()
	{

	}
}
