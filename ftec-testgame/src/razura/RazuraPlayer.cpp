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

#include "logger/log.h"

namespace ftec {
	RazuraPlayer::RazuraPlayer()
		: m_Position(0, 0, 0)
	{
		m_Sprite = Sprite(Engine::getResourceManager().load<Texture>("sprites/player.png"));
		m_Sprite2 = Sprite(Engine::getResourceManager().load<Texture>("textures/pixel_test.png"));

		m_Sprite.size().width /= 20.0f;
		m_Sprite.size().height /= 20.0f;
		m_Sprite2.size().width = 1.0f;
		m_Sprite2.size().height = 1.0f;

		m_Sprite.offset().x = 0.5f;
		m_Sprite.offset().y = 0;

		m_Sprite2.offset().x = 0.5f;
		m_Sprite2.offset().y = 0.5f;
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
			m_Position += motion * 2 * Time::deltaTime;
		}
		m_Position.z = 0;
	}

	void RazuraPlayer::render2D(Graphics2D & graphics)
	{
		graphics.drawSprite(m_Sprite, getIsometricTransformationMatrix(m_Position));

		graphics.drawSprite(m_Sprite, getIsometricTransformationMatrix(Vector3f(1, 0, 0)));
		graphics.drawSprite(m_Sprite, getIsometricTransformationMatrix(Vector3f(0, 1, 0)));
		graphics.drawSprite(m_Sprite, getIsometricTransformationMatrix(Vector3f(-1, 0, 0)));
		graphics.drawSprite(m_Sprite, getIsometricTransformationMatrix(Vector3f(0, -1, 0)));


		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(-1, 0, 0), true));
		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(-1, 1, 0), true));
		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(-1, -1, 0), true));

		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(0, 0, 0), true));
		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(0, 1, 0), true));
		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(0, -1, 0), true));

		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(1, 0, 0), true));
		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(1, 1, 0), true));
		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(1, -1, 0), true));

		graphics.setColor(Color32::red());
		graphics.drawSprite(m_Sprite2, getIsometricTransformationMatrix(Vector3f(
			Time::sinTime, 
			Time::cosTime,
			0.1f), true));
		graphics.setColor(Color32::white());

		/*Matrix3f transform({
			1,0,m_Position.x,
			0,1,m_Position.y,
			0,0,m_Position.y
		});

		Matrix3f transform1({
			1,0, 0,
			0,1, 0.1f,
			0,0, 0.1f
		});
		Matrix3f transform2({
			1,0, 0,
			0,1, 0.2f,
			0,0, 0.2f
		});


		graphics.drawSprite(m_Sprite, transform);
		graphics.drawSprite(m_Sprite, transform1);
		graphics.drawSprite(m_Sprite, transform2);

		float height = Time::sin2Time / 8 + 0.125f;
		float height2 = Time::cos2Time / 8 + 0.125f;
		float yPos = 0;

		Matrix3f transform3({
			1,0, 0,
			0,1, yPos + height,
			0,1, yPos - height
		});

		Matrix3f transform4({
			1,0, 0,
			0,1, yPos + height2,
			0,1, yPos - height2
		});

		graphics.drawSprite(m_Sprite2, transform3);

		graphics.setColor(Color32::red());

		graphics.drawSprite(m_Sprite2, transform4);
		
		graphics.setColor(Color32::white());*/
	}

}
