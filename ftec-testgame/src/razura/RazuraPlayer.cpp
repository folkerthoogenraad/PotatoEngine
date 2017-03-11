#include "RazuraPlayer.h"

#include "graphics/Graphics2D.h"

#include "engine/Time.h"
#include "engine/Input.h"
#include "engine/Keycodes.h"

#include "graphics/Graphics.h"
#include "math/Matrix4.h"

#include "engine/Engine.h"
#include "resources/ResourceManager.h"

#include "isometric/isometric_helpers.h"

namespace ftec {
	RazuraPlayer::RazuraPlayer()
		: m_Position(0, 0, 0)
	{
		m_Sprite = Sprite(Engine::getResourceManager().load<Texture>("sprites/player.png"));

		m_Sprite.size().width /= 20.0f;
		m_Sprite.size().height /= 20.0f;
		
		m_Sprite.offset().x = 0.5f;
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
		Vector3f motion(0, 0, 0);

		if (Input::isKeyDown(KEY_W)) {
			motion.z += 1;
		}if (Input::isKeyDown(KEY_S)) {
			motion.z -= 1;
		}if (Input::isKeyDown(KEY_A)) {
			motion.x -= 1;
		}if (Input::isKeyDown(KEY_D)) {
			motion.x += 1;
		}

		if (motion.sqrmagnitude() > 0) {
			motion.normalize();
			m_Position += motion * 2 * Time::deltaTime;
		}
	}

	void RazuraPlayer::render2D(Graphics2D & graphics)
	{
		graphics.drawSprite(m_Sprite, isometricTransform(m_Position));
	}

}
