#include "Razura.h"

#include "engine/Engine.h"
#include "engine/Time.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"

#include "math/math.h"
#include "math/Vector2.h"
#include "math/Vector4.h"
#include "math/Matrix4.h"
#include "math/Quaternion.h"

#include "resources/ResourceManager.h"

#include "scene/Entity.h"
#include "scene/Scene.h"

#include "graphics/Renderer.h"
#include "graphics/Graphics2D.h"
#include "graphics/Window.h"
#include "graphics/Sprite.h"
#include "graphics/Graphics.h"
#include "graphics/Mesh.h"

#include "NoClipCameraEntity.h"

#include "logger/log.h"

namespace ftec {

	void Razura::update()
	{ }

	void Razura::render()
	{
		Renderer::clear();
	}

	struct TestEntity : public Entity
	{
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<PBRMaterial> m_Material;

		Quaternionf angle;

		TestEntity()
		{
			angle = Quaternionf::identity();

			m_Material = std::make_shared<PBRMaterial>();

			//God please rename these man.
			m_Material->m_TextureMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
			m_Material->m_NormalMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_NORMAL);

			m_Material->m_MetallicMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_GRAY);
			m_Material->m_RoughnessMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_BLACK);

			m_Material->m_Shader = Engine::getResourceManager().load<Shader>("shaders/default");
			
			m_Mesh = Engine::getResourceManager().load<Mesh>("mesh/monkey.obj");
		}

		void update()
		{
			if (Input::isMouseButtonDown(MOUSE_BUTTON_LEFT)){
				angle *= Quaternionf::fromEuler(Vector3f(Input::getMouseDY() * -0.005f, Input::getMouseDX() * -0.005f, 0));
			}
			else {
				angle *= Quaternionf::fromEuler(Vector3f(0, Time::deltaTime * 0.1f, 0));
			}
		}

		void render3D()
		{
			Graphics::enqueueMesh(m_Mesh.get(), m_Material.get(), 
				Matrix4f::translation(Vector3f(0, 0, -3)) * 
				angle.matrix());
		}
	};

	void Razura::init()
	{
		auto scene = std::make_unique<Scene>();
		scene->setMode(Scene::GRAPHICS_3D);

		scene->m_Cameras[0] = Camera::perspective(60, Engine::getWindow().getAspectRatio(), 0.01f, 100.0f);

		scene->addEntity(std::make_unique<NoClipCameraEntity>());
		scene->addEntity(std::make_unique<TestEntity>());

		Engine::setScene(std::move(scene));
	}

	void Razura::destroy()
	{ }
}
