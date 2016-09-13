#include "NoClipCameraEntity.h"
#include "logger/log.h"
#include "engine/Engine.h"
#include "engine/Time.h"
#include "engine/Input.h"

namespace ftec {
	NoClipCameraEntity::NoClipCameraEntity()
	{
	}
	NoClipCameraEntity::~NoClipCameraEntity()
	{
	}

	void NoClipCameraEntity::update()
	{
		Camera &cam = Engine::getScene()->m_Camera;

		cam.m_Yaw += Input::getMouseDX() / 10.f;
		cam.m_Pitch += Input::getMouseDY() / 10.f;


		if (cam.m_Pitch > 90)
			cam.m_Pitch = 90;
		if (cam.m_Pitch < -90)
			cam.m_Pitch = -90;

		vec3 motion;

		if (Input::isKeyDown(GLFW_KEY_W)) {
			motion.z += 1;
		}if (Input::isKeyDown(GLFW_KEY_S)) {
			motion.z -= 1;
		}if (Input::isKeyDown(GLFW_KEY_A)) {
			motion.x += 1;
		}if (Input::isKeyDown(GLFW_KEY_D)) {
			motion.x -= 1;
		}
		
		mat4 transform = mat4::rotation(cam.m_Yaw, vec3(0,1,0)) * mat4::rotation(cam.m_Pitch, vec3(1,0,0));
		motion = transform * motion;

		motion.y = 0;
		if (Input::isKeyDown(GLFW_KEY_Q)) {
			motion.y -= 1;
		}if (Input::isKeyDown(GLFW_KEY_Z)) {
			motion.y += 1;
		}

		cam.m_Position += motion * 3.f * Time::deltaTime;
	}

	void NoClipCameraEntity::render()
	{

	}
}