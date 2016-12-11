#include "Razura.h"

#include "engine/Engine.h"
#include "engine/Time.h"

#include "math/math.h"
#include "math/Vector2.h"
#include "math/Vector4.h"

#include "resources/ResourceManager.h"

#include "scene/Entity.h"
#include "scene/Scene.h"

#include "graphics/Renderer.h"
#include "graphics/Graphics2D.h"
#include "graphics/Window.h"
#include "graphics/Sprite.h"

#include "logger/log.h"

#define RANDOM ((rand() % 1000) / 1000.0f)

namespace ftec {

	void Razura::update()
	{ }

	void Razura::render()
	{
		Renderer::clear();
	}

	struct TestEntity : public Entity
	{
		Vector2f m_Direction;
		Sprite m_Sprite;

		TestEntity()
		{
			m_Position.x = RANDOM * 20 - 10;
			m_Position.y = RANDOM * 10 - 5;

			m_Direction.x = -5.0f * RANDOM;
			m_Direction.y =  0.0f;

			auto texture = Engine::getResourceManager().load<Texture>("textures/test_image.png");
			texture->setScaling(Texture::InterpolationMode::LINEAR, Texture::InterpolationMode::LINEAR);

			m_Sprite = Sprite(
				texture
			);

			float size = RANDOM * 5;
			m_Sprite.bounds() = Rectanglef::centered(0, 0, size, size);
		}

		void update()
		{
			m_Position.x += Time::deltaTime * m_Direction.x;
			m_Position.y += Time::deltaTime * m_Direction.y;

			if (m_Position.x < -12)
				m_Position.x += 24;
		}

		void render2D(Graphics2D &graphics) override 
		{
			graphics.setDepth(m_Direction.x);

			graphics.setColor(Color32::white());
			graphics.drawSprite(m_Sprite, Vector2f(m_Position.x, m_Position.y));
		};
	};

	void Razura::init()
	{
		auto scene = std::make_unique<Scene>();
		scene->setMode(Scene::GRAPHICS_2D);

		scene->m_Cameras[0] = Camera::orthagonal(5, Engine::getWindow().getAspectRatio(), -100, 100);

		for(int i = 0; i < 1000; i++)
			scene->addEntity(std::make_unique<TestEntity>());

		Engine::setScene(std::move(scene));
	}

	void Razura::destroy()
	{ }
}
