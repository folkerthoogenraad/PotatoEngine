#include "RazuraPlayer.h"

#include <array>

#include "graphics/Graphics2D.h"

#include "engine/Time.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"

#include "graphics/Graphics.h"
#include "math/Matrix4.h"

#include "scene/Scene.h"

#include "RazuraWorldEntity.h"
#include "math/collision.h"

#include "math/Vector2.h"

#include <assert.h>

namespace ftec {
	RazuraPlayer::RazuraPlayer()
		: m_Position(0, 0, 0)
	{
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
		Vector2f motion(0, 0);

		if (Input::isKeyDown(KEY_W)) {
			motion.y += 1;
		}if (Input::isKeyDown(KEY_S)) {
			motion.y -= 1;
		}if (Input::isKeyDown(KEY_A)) {
			motion.x -= 1;
		}if (Input::isKeyDown(KEY_D)) {
			motion.x += 1;
		}

		if (motion.sqrmagnitude() > 0) {
			motion.normalize();
			motion *= 4 * Time::deltaTime;
		}

		Vector2f p = Vector2f(m_Position.x, m_Position.y);

		Line2f motionLine(p, p + motion);
		Vector2f direction = motionLine.direction().normalize();

		//Collision testing
		m_Scene->forEach([&](const Entity *entity) {
			const RazuraWorldEntity *rwe = dynamic_cast<const RazuraWorldEntity*>(entity);

			if (!rwe)
				return;

			Rectanglef toCheck = rwe->m_Bounds;

			//Use the whatever product 
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

				Line2f line(loop[from], loop[to]);

				// Don't check the wrong side
				if (Vector2f::dot(line.normal().direction().normalize(), direction) > 0)
					continue;

				CollisionResult<Vector2f> result = intersectSegment(motionLine, line);

				if (result) {
					float dist = motionLine.length();
					float nDist = (motionLine.a - *result).magnitude();
					if (nDist < dist) {
						motionLine.b = *result;
					}
				}
			}
		});

		m_Position.x = motionLine.b.x;
		m_Position.y = motionLine.b.y;
	}

	void RazuraPlayer::render2D(Graphics2D &graphics)
	{
		graphics.setColor(Color32::red());
		graphics.drawRectangle(Rectanglef::centered(m_Position.x, m_Position.y, 1, 1), true);
	}

}
