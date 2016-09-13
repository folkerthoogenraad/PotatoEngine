#include "Input.h"
#include "Engine.h"

namespace ftec {

	std::set<int> Input::downKeys = std::set<int>();
	std::set<int> Input::pressedKeys = std::set<int>();
	std::set<int> Input::releasedKeys = std::set<int>();
	vec2 Input::mousePosition = vec2();
	vec2 Input::mouseDelta = vec2();

	vec2 Input::getMousePosition()
	{
		return mousePosition;
	}

	vec2 Input::getMouseDelta()
	{
		return mouseDelta;
	}

	void Input::setCursorMode(int mode)
	{
		Engine::getWindow().setCursorMode(mode);
	}

	void Input::reset()
	{
		pressedKeys.clear();
		releasedKeys.clear();
		mouseDelta = vec2();

	}

	void Input::handleKey(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			pressedKeys.insert(key);
			downKeys.insert(key);
		}
		if (action == GLFW_RELEASE) {
			releasedKeys.insert(key);
			downKeys.erase(key);
		}
	}

	void Input::handleCursor(float x, float y)
	{
		vec2 newPosition(x, y);
		mouseDelta = newPosition - mousePosition;
		mousePosition = newPosition;
	}

	bool Input::isKeyDown(int keycode)
	{
		return downKeys.find(keycode) != downKeys.end();
	}

	bool Input::isKeyPressed(int keycode)
	{
		return pressedKeys.find(keycode) != pressedKeys.end();
	}

	bool Input::isKeyReleased(int keycode)
	{
		return releasedKeys.find(keycode) != releasedKeys.end();
	}

	float Input::getMouseX()
	{
		return mousePosition.x;
	}
	float Input::getMouseY()
	{
		return mousePosition.y;
	}
	float Input::getMouseDX()
	{
		return mouseDelta.x;
	}
	float Input::getMouseDY()
	{
		return mouseDelta.y;
	}

}