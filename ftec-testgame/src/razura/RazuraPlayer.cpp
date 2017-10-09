#include "RazuraPlayer.h"

#include <array>

#include "graphics/Graphics2D.h"

#include "engine/Time.h"
#include "engine/Engine.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"
#include "resources/ResourceManager.h"

#include "graphics/Graphics.h"
#include "math/Matrix4.h"

#include "scene/Scene.h"

#include "RazuraWorldEntity.h"
#include "math/collision.h"

#include "math/Vector2.h"

#include <assert.h>

#include "isometric/isometric_helpers.h"

#include "logger/log.h"

namespace ftec {
	RazuraPlayer::RazuraPlayer()
		: m_Position(0, 0)
	{
		m_Sprite = Sprite(Engine::getResourceManager().load<Texture>("sprites/player.png"));

		m_Sprite.offset() = Vector2f(0.5f, 0.5f);
	}

	RazuraPlayer::~RazuraPlayer()
	{
	}

	void RazuraPlayer::onStart()
	{

	}

	void RazuraPlayer::onEnd()
	{
	}

	void RazuraPlayer::update()
	{
		float m = m_Motion.x;

		const float grav = 32;
		const float accel = 16;
		const float jmp = 10;
		const float spd = 4;

		if (Input::isKeyDown(KEY_A)) {
			m -= accel * Time::deltaTime;
		}if (Input::isKeyDown(KEY_D)) {
			m += accel * Time::deltaTime;
		}if (Input::isKeyPressed(KEY_SPACE)) {
			m_Motion.y = jmp;
		}

		if (m > spd)
			m = spd;
		if (m < -spd)
			m = -spd;

		m_Motion.x = m;
		m_Motion.y -= grav * Time::deltaTime;

		//Collision testing
		Line2f motionLine(m_Position, m_Position + m_Motion * Time::deltaTime);
		Vector2f direction = motionLine.direction().normalize();

		m_Scene->forEach([&](const Entity *entity) {
			const RazuraWorldEntity *rwe = dynamic_cast<const RazuraWorldEntity*>(entity);

			if (!rwe)
				return;

			Rectanglef toCheck = rwe->m_Bounds;

			// Use the whatever product 
			toCheck.x() -= 0.5f;
			toCheck.y() -= 0.5f;
			toCheck.width() += 1.0f;
			toCheck.height() += 1.0f;

			std::array<Vector2f, 4> loop{
				toCheck.topleft(),
				toCheck.topright(),
				toCheck.bottomright(),
				toCheck.bottomleft()
			};

			for (int i = 0; i < loop.size(); i++) {
				int from = i;
				int to = (i + 1) % loop.size();

				// Setup all the line variables
				Line2f line(loop[from], loop[to]);

				Vector2f lineNormal = line.normal().direction().normalize();
				Vector2f lineTangent = line.direction().normalize();

				float length = line.direction().magnitude();

				// If the motion and the line are in the same direction, we can just ignore the results
				if (Vector2f::dot(lineNormal, direction) > 0)
					continue;

				if (Vector2f::dot(lineNormal, motionLine.a - line.a) < 0)
					continue;

				if (Vector2f::dot(lineNormal, motionLine.b - line.a) > 0)
					continue;


				auto result = intersect(line, motionLine);

				if (result) {
					float t = Vector2f::dot(lineTangent, *result - line.a);
					
					if (t <= 0)
						continue;
					if (t >= length)
						continue;

					{
						float d = Vector2f::dot(lineNormal, motionLine.b - line.a);

						motionLine.b -= d * lineNormal;
					}
					{/*
						float d = Vector2f::dot(lineNormal, motionLine.b - line.a);
						motionLine.b = *result;
					*/}
				}
			}
		});

		m_Position.x = motionLine.b.x;
		m_Position.y = motionLine.b.y;

		m_Motion = motionLine.direction() / Time::deltaTime;

	}

	void RazuraPlayer::render2D(Graphics2D &graphics)
	{
		//graphics.setColor(Color32::white());
		//graphics.drawSprite(m_Sprite, Matrix3f::translation(m_Position));
		graphics.setColor(Color32::red());
		graphics.drawRectangle(Rectanglef::centered(m_Position.x, m_Position.y, 1, 1), true);
	}

}
