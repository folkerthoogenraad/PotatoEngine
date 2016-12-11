#include "Razura.h"

#include "engine/Engine.h"
#include "engine/Time.h"

#include "math/math.h"

#include "scene/Entity.h"
#include "scene/Scene.h"

#include "graphics/Renderer.h"

#include "logger/log.h"

#define RANDOM ((rand() % 1000) / 1000.0)


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
		Color32 m_Color;

		TestEntity()
		{
			m_Position.x = RANDOM * 20 - 10;
			m_Position.y = RANDOM * 10 - 5;

			m_Color = Color32(RANDOM * 255, RANDOM * 255, RANDOM * 255, 255);

			//TODO find out where this rand came from
			m_Direction.x =-10.0f;
			m_Direction.y =  0.0f;
		}

		void update()
		{
			m_Position.x += Time::deltaTime * m_Direction.x;
			m_Position.y += Time::deltaTime * m_Direction.y;

			if (m_Position.x < -10)
				m_Position.x += 20;
		}

		void render2D(Graphics2D &graphics) override 
		{
			graphics.setColor(m_Color);
			graphics.drawRectangle(Rectanglef::centered(
				m_Position.x, m_Position.y, 1.f,1.f
			), true);
		};
	};

	void Razura::init()
	{
		auto scene = std::make_unique<Scene>();
		scene->setMode(Scene::GRAPHICS_2D);

		scene->m_Cameras[0] = Camera::orthagonal(5, 16.f / 9.f, -100, 100);

		scene->addEntity(std::make_unique<TestEntity>());

		Engine::setScene(std::move(scene));
	}

	void Razura::destroy()
	{ }
}
