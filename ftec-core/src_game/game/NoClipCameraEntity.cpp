#include "NoClipCameraEntity.h"
#include "logger/log.h"
#include "engine/Engine.h"
#include "engine/Time.h"

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

		cam.m_Position.z = Time::sinTime;
		cam.m_Position.y = Time::cosTime / 4.f + 1.7f;
	}

	void NoClipCameraEntity::render()
	{

	}
}
