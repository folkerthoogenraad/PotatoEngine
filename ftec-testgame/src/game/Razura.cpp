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
#include "potato_ui/Checkbox.h"
#include "potato_ui/Slider.h"
#include "potato_ui/Label.h"
#include "potato_ui/Dropdown.h"
#include "potato_ui/LinearLayout.h"
#include "potato_ui/LayoutParams.h"
#include "potato_ui/TabbedPanel.h"
#include "potato_ui/SceneView.h"
#include "graphics/Renderer.h"

#include "potato_ui/UILoader.h"

namespace ftec {


	void Razura::update()
	{
		ui->update();
	}


	void Razura::render()
	{
		ui->render();
	}

	void Razura::init()
	{
		//UI
		{
			ui = std::make_shared<potato::PotatoUI>();

			ui->setRoot(
				potato::UILoader::load("text.xml")
			);
		}
	
		//3D stuff
		{
			std::shared_ptr<Scene> scene = std::make_shared<Scene>();
			Engine::setScene(scene);

			scene->m_Light.m_Direction = vec3f(1,-0.4f,-1).normalize();

			auto sphere = Engine::getResourceManager().load<Mesh>("mesh/sphere.obj");

			for (int x = 0; x < 5; x++) {
				for (int y = 0; y < 5; y++) {
					Material material = {
						Engine::getResourceManager().load<Texture>("textures/metal/metal_albedo.tif"),
						Engine::getResourceManager().load<Shader>("shaders/default")
					};
					material.m_Metallicness = x / 5.0f;
					material.m_Roughness = y / 5.0f;
					
					material.m_NormalMap = Engine::getResourceManager().load<Texture>("textures/metal/metal_normal.tif");
					material.m_RoughnessMap = Engine::getResourceManager().load<Texture>("textures/metal/metal_roughness.tif");
					material.m_MetallicMap = Engine::getResourceManager().load<Texture>("textures/metal/metal_metallicness.tif");

					material.m_Tiling = vec2f(4, 4);

					scene->addMesh(vec3f(x * 2.5, 0, y * 2.5), sphere, material);
				}
			}

			
			scene->addEntity(std::make_shared<NoClipCameraEntity>());
		}
	}

	void Razura::destroy()
	{

	}
}
