#include "Input.h"
#include "Engine.h"

namespace ftec {

	std::set<int> Input::downKeys = std::set<int>();
	std::set<int> Input::pressedKeys = std::set<int>();
	std::set<int> Input::releasedKeys = std::set<int>();
	std::set<int> Input::typedKeys = std::set<int>();
	std::string Input::keystring = "";
	vec2f Input::mousePosition = vec2f();
	vec2f Input::mouseDelta = vec2f();
	vec2f Input::scrollDelta = vec2f();

	vec2f Input::getMousePosition()
	{
		return mousePosition;
	}

	vec2f Input::getMouseDelta()
	{
		return mouseDelta;
	}

	vec2f Input::getScroll()
	{
		return scrollDelta;
	}

	void Input::setCursorMode(int mode)
	{
		Engine::getWindow().setCursorMode(mode);
	}

	void Input::reset()
	{
		pressedKeys.clear();
		releasedKeys.clear();
		typedKeys.clear();
		mouseDelta = vec2f();
		scrollDelta = vec2f();
		keystring = "";
	}

	void Input::handleKey(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			pressedKeys.insert(key);
			downKeys.insert(key);
			typedKeys.insert(key);
		}
		if (action == GLFW_RELEASE) {
			releasedKeys.insert(key);
			downKeys.erase(key);
		}
		if (action == GLFW_REPEAT) {
			typedKeys.insert(key);
		}

	}


	void Input::handleCursor(float x, float y)
	{
		vec2f newPosition(x, y);
		mouseDelta += newPosition - mousePosition;
		mousePosition = newPosition;
	}

	void Input::handleScroll(float x, float y)
	{
		scrollDelta += vec2f(x, y);
	}

	void Input::handleTyped(unsigned int unicode)
	{
		keystring += (char)unicode;
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

	bool Input::isKeyTyped(int keycode)
	{
		return typedKeys.find(keycode) != typedKeys.end();
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
