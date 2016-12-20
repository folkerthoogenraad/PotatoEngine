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
#include "Voronoi3DEntity.h"

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
		Vector2f m_Position;
		float m_Speed = 4;
		Sprite sprite;

		TestEntity(Vector2f position)
		{
			m_Position = position;
			sprite = Sprite(Engine::getResourceManager().load<Texture>("textures/mario.png"));
			sprite.bounds() = Rectanglef::centered(0, 0, 1, 1);
		}

		void update()
		{
			Vector2f velocity = Vector2f();

			if (Input::isKeyDown(KEY_LEFT)) {
				velocity.x -= 1;
			}
			if (Input::isKeyDown(KEY_RIGHT)) {
				velocity.x += 1;
			}
			if (Input::isKeyDown(KEY_UP)) {
				velocity.y += 1;
			}
			if (Input::isKeyDown(KEY_DOWN)) {
				velocity.y -= 1;
			}

			if (velocity.magnitude() > 0) {
				velocity.normalize();
				m_Position += velocity * (m_Speed * Time::deltaTime);
			}

		}
		
		void render2D(Graphics2D &graphics) override
		{
			graphics.setDepth(4);
			graphics.setColor(Color32::yellow());
			graphics.drawRectangle(Rectanglef::centered(0, 0, 1, 1), true);
			graphics.setDepth(8);
			graphics.setColor(Color32::red());
			graphics.drawRectangle(Rectanglef::centered(0.5f, 0.5f, 1, 1), true);

			graphics.setDepth(1.0f);
			graphics.setColor(Color32::white());
			graphics.drawSprite(sprite, m_Position);
		
			graphics.setLineWidth(0.01f);
			graphics.setColor(Color32::white());
			graphics.drawLine(Line2f(Vector2f(0,0), Vector2f(1,1)));
		}

	};

	void Razura::init()
	{
		auto scene = std::make_unique<Scene>();
		scene->setMode(Scene::GRAPHICS_2D);

		scene->m_Cameras[0] = Camera::orthagonal(5, Engine::getWindow().getAspectRatio(), 0.01f, 100.0f);
		//scene->m_Cameras[0] = Camera::perspective(60, Engine::getWindow().getAspectRatio(), 0.01f, 100.0f);
		
		scene->addEntity(std::make_unique<NoClipCameraEntity>());
		scene->addEntity(std::make_unique<Voronoi3DEntity>());
		scene->addEntity(std::make_unique<TestEntity>(Vector2f(0,0)));

		Engine::setScene(std::move(scene));
	}

	void Razura::destroy()
	{ }
}
