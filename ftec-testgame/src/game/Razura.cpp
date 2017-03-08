#include "Razura.h"

#include "engine/Engine.h"
#include "engine/Input.h"
#include "logger/log.h"
#include "resources/ResourceManager.h"

#include "scene/Scene.h"

#include "math/Matrix4.h"

#include "graphics/Renderer.h"
#include "graphics/Window.h"
#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "graphics/Graphics.h"

#include "razura/RazuraPlayer.h"
#include "razura/RazuraWorldEntity.h"

#include "potato_ui/PotatoUI.h"
#include "potato_ui/Button.h"
#include "potato_ui/LinearLayout.h"
#include "potato_ui/Slider.h"
#include "potato_ui/TextField.h"

#include "NoClipCameraEntity.h"

#include "potato_ui/Event.h"
#include "potato_ui/EventInput.h"

#include "TestCanvas.h"

namespace ftec {

	const float PIXEL_UNIT_WIDTH = 0.79056941504; // (1/2 * sqrt(2)) / (cos( atan(1/2) ))
	const float PIXEL_UNIT_HEIGHT = 0.86602540378;

	const int PIXELS_PER_UNIT = 32;

	const float SQRT_2 = 1.41421356237;

	void Razura::update()
	{ 
		if (m_UI)
			m_UI->update();
	}

	const int tiles = 4;

	class TestTempEntity : public Entity{
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<PBRMaterial> material;
	
		float heights[tiles * tiles];
	public:
		TestTempEntity()
		{
			material = std::make_shared<PBRMaterial>(
				Engine::getResourceManager().load<Texture>("textures/pixel_test.png"),
				Engine::getResourceManager().load<Shader>("shaders/diffuse")
				);

			material->m_NormalMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);
			material->m_RoughnessMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);
			material->m_MetallicMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);

			mesh = Engine::getResourceManager().load<Mesh>("mesh/cube.obj");

			for (int x = 0; x < tiles; x++) {
				for (int y = 0; y < tiles; y++) {
					heights[x + y * tiles] = (rand() % (PIXELS_PER_UNIT / 2)) / (float)(PIXELS_PER_UNIT / 2);
				}
			}
		}

		float offset = 0.00f;

		void render() override
		{
			const float scale = 1.2248 - offset;

			if (Input::isKeyTyped(KEY_UP)){
				offset += 0.0001f;
				LOG("Offset: " << offset << ", Scale : " << scale);
			}
			if (Input::isKeyTyped(KEY_DOWN)) {
				offset -= 0.0001f;
				LOG("Offset: " << offset << ", Scale : " << scale);
			}

			Matrix4f center = Matrix4f::scaled(scale, 1, scale);

			for (int x = 0; x < tiles; x++) {
				for (int y = 0; y < tiles; y++) {
					Graphics::enqueueMesh(mesh.get(), material.get(), center * Matrix4f::translation(x - tiles / 2, heights[x + y * tiles], y - tiles / 2));
				}
			}
		}
	};


	void Razura::render()
	{
		Renderer::clear();

		if (m_UI)
			m_UI->render();
	}

	void Razura::init()
	{
		/*{
			m_UI = std::make_shared<potato::PotatoUI>();
			auto layout = std::make_shared<potato::LinearLayout>(potato::LinearLayout::VERTICAL);

			auto b = std::make_shared<potato::Button>("abcdefghijklmn");
			b->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;
			auto b2 = std::make_shared<potato::Button>("more stuff");
			b2->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;

			auto tf = std::make_shared<potato::TextField>();
			tf->layoutparams().m_WidthScaling = potato::LayoutParams::MATCH_PARENT;
			tf->layoutparams().m_Weight = 2.0f;
			tf->hint() = "test text";

			layout->addPanel(b);
			layout->addPanel(std::make_shared<potato::Button>("Hello world"));
			layout->addPanel(std::make_shared<potato::Button>("abcdefghijklmn"));
			layout->addPanel(b2);
			layout->addPanel(tf);
			layout->addPanel(std::make_shared<TestCanvas>());

			m_UI->setRoot(
				layout
			);
		}*/

		{
			auto scene = std::make_unique<Scene>();
			scene->setMode(Scene::SceneMode::GRAPHICS_BOTH);

			//16 px per unit
			scene->m_Cameras[0] = Camera::orthagonal(Engine::getWindow().getHeight() / PIXELS_PER_UNIT * PIXEL_UNIT_HEIGHT, 16.0f / 9.0f, 0.1f, 100, false);

			//scene->m_Cameras[0] = Camera::perspective(60, 16.0f / 9.0f, 0.1f, 100);
			scene->m_Cameras[0].m_Position = Vector3f(-10, 10, -10);
			scene->m_Cameras[0].m_Yaw = -45.0f;
			scene->m_Cameras[0].m_Pitch = -30.0f;

			LOG(scene->m_Cameras[0].getViewMatrix());

			scene->addEntity(std::make_unique<NoClipCameraEntity>());
			scene->addEntity(std::make_unique<TestTempEntity>());

			Engine::setScene(std::move(scene));
		}
	}

	void Razura::destroy()
	{ }
}
