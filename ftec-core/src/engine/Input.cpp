#include "Input.h"

#include "Engine.h"
#include "graphics/Window.h"

#include <assert.h>

namespace ftec {

	static std::set<int> downKeys = std::set<int>();
	static std::set<int> pressedKeys = std::set<int>();
	static std::set<int> releasedKeys = std::set<int>();
	static std::set<int> typedKeys = std::set<int>();

	static std::set<int> downMouse = std::set<int>();
	static std::set<int> pressedMouse = std::set<int>();
	static std::set<int> releasedMouse = std::set<int>();

	static CursorMode cursorMode = CursorMode::NORMAL;
	static bool disabled = false;

	static std::string keystring = "";
	static Vector2f mousePosition = Vector2f();
	static Vector2f mouseDelta = Vector2f();
	static Vector2f scrollDelta = Vector2f();

	Vector2f Input::getMousePosition()
	{
		return mousePosition;
	}

	Vector2f Input::getMouseDelta()
	{
		return disabled ? Vector2f() : mouseDelta;
	}

	Vector2f Input::getScroll()
	{
		return disabled ? Vector2f() : scrollDelta;
	}

	void Input::setCursorMode(CursorMode mode)
	{
		cursorMode = mode;
		int c = -1;
		
		if (mode == CursorMode::GRABBED)
			c = GLFW_CURSOR_DISABLED;
		else if (mode == CursorMode::NORMAL)
			c = GLFW_CURSOR_NORMAL;
		else if (mode == CursorMode::HIDDEN)
			c = GLFW_CURSOR_HIDDEN;
		else
			assert(false);

		Engine::getWindow().setCursorMode(c);
	}


	void Input::reset()
	{
		pressedKeys.clear();
		releasedKeys.clear();
		typedKeys.clear();
		pressedMouse.clear();
		releasedMouse.clear();
		mouseDelta = Vector2f();
		scrollDelta = Vector2f();
		keystring = "";
	}

	void Input::setEnabled(bool e)
	{
		disabled = !e;
	}

	bool Input::isEnabled()
	{
		return !disabled;
	}

	const std::string & Input::getKeyString()
	{
		return keystring;
	}

	const std::set<int>& Input::getKeysDown()
	{
		return downKeys;
	}

	const std::set<int>& Input::getKeysPressed()
	{
		return pressedKeys;
	}

	const std::set<int>& Input::getKeysReleased()
	{
		return releasedKeys;
	}

	const std::set<int>& Input::getKeysTyped()
	{
		return typedKeys;
	}

	const std::set<int>& Input::getMouseButtonsDown()
	{
		return downMouse;
	}

	const std::set<int>& Input::getMouseButtonsPressed()
	{
		return pressedMouse;
	}

	const std::set<int>& Input::getMouseButtonsReleased()
	{
		return releasedMouse;
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
		Vector2f newPosition(x, y);
		mouseDelta += newPosition - mousePosition;
		if (cursorMode != CursorMode::GRABBED) {
			mousePosition = newPosition;
		}
		else {
			Engine::getWindow().setMousePosition(mousePosition);
		}

	}

	void Input::handleScroll(float x, float y)
	{
		scrollDelta += Vector2f(x, y);
	}

	void Input::handleTyped(unsigned int unicode)
	{
		keystring += (char)unicode;
	}

	void Input::handleMouse(int button, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			pressedMouse.insert(button);
			downMouse.insert(button);
		}
		if (action == GLFW_RELEASE) {
			releasedMouse.insert(button);
			downMouse.erase(button);
		}
	}

	bool Input::isKeyDown(int keycode)
	{
		return !disabled && downKeys.find(keycode) != downKeys.end();
	}

	bool Input::isKeyPressed(int keycode)
	{
		return !disabled && pressedKeys.find(keycode) != pressedKeys.end();
	}

	bool Input::isKeyReleased(int keycode)
	{
		return !disabled && releasedKeys.find(keycode) != releasedKeys.end();
	}

	bool Input::isKeyTyped(int keycode)
	{
		return !disabled && typedKeys.find(keycode) != typedKeys.end();
	}

	bool Input::isMouseButtonPressed(int keycode)
	{
		return !disabled && pressedMouse.find(keycode) != pressedMouse.end();
	}

	bool Input::isMouseButtonDown(int keycode)
	{
		return !disabled && downMouse.find(keycode) != downMouse.end();
	}

	bool Input::isMouseButtonReleased(int keycode)
	{
		return !disabled && releasedMouse.find(keycode) != releasedMouse.end();
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
		return disabled ? 0 : mouseDelta.x;
	}
	float Input::getMouseDY()
	{
		return disabled ? 0 : mouseDelta.y;
	}

}
