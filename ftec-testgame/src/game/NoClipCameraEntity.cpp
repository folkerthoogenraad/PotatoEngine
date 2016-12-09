#include "logger/log.h"

#include "NoClipCameraEntity.h"

#include "engine/Engine.h"
#include "engine/Time.h"
#include "engine/Input.h"

#include "math/Matrix4.h" //Why was this already included?
#include "math/Vector3.h"

#include "graphics/Camera.h"
#include "scene/Scene.h"

namespace ftec {
	NoClipCameraEntity::NoClipCameraEntity() : m_MouseGrabbed(false)
	{ }

	NoClipCameraEntity::~NoClipCameraEntity()
	{ }

	void NoClipCameraEntity::update()
	{
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
			m_MouseGrabbed = !m_MouseGrabbed;
			Input::setCursorMode(m_MouseGrabbed ? CursorMode::GRABBED : CursorMode::NORMAL);
		}

		if (m_MouseGrabbed) {
			Camera &cam = Engine::getScene()->m_Camera;

			cam.m_Yaw += Input::getMouseDX() / 10.f;
			cam.m_Pitch += Input::getMouseDY() / 10.f;


			if (cam.m_Pitch > 90)
				cam.m_Pitch = 90;
			if (cam.m_Pitch < -90)
				cam.m_Pitch = -90;

			Vector3f motion;

			if (Input::isKeyDown(GLFW_KEY_W)) {
				motion.z -= 1;
			}if (Input::isKeyDown(GLFW_KEY_S)) {
				motion.z += 1;
			}if (Input::isKeyDown(GLFW_KEY_A)) {
				motion.x -= 1;
			}if (Input::isKeyDown(GLFW_KEY_D)) {
				motion.x += 1;
			}

			Matrix4f transform = Matrix4f::rotation(cam.m_Yaw, Vector3f(0, 1, 0));
			motion = transform * motion;

			motion.y = 0;
			if (Input::isKeyDown(GLFW_KEY_Q)) {
				motion.y += 1;
			}if (Input::isKeyDown(GLFW_KEY_Z)) {
				motion.y -= 1;
			}

			if (motion.magnitude() > 1) {
				motion.normalize();
			}

			cam.m_Position += motion * 3.f * Time::deltaTime;
		}
		
		
	}

	void NoClipCameraEntity::render()
	{ }
}
