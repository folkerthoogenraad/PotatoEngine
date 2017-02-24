#include "Input.h"

#include "Engine.h"

#include "graphics/GL.h"
#include "graphics/Window.h"

#include "math/Vector2.h"

#include <assert.h>
#include <array>

#include "logger/log.h"

namespace ftec {

	static std::set<int> downKeys = std::set<int>();
	static std::set<int> pressedKeys = std::set<int>();
	static std::set<int> releasedKeys = std::set<int>();

	static std::vector<TypeInput> typedKeys = std::vector<TypeInput>();

	static std::set<int> downMouse = std::set<int>();
	static std::set<int> pressedMouse = std::set<int>();
	static std::set<int> releasedMouse = std::set<int>();

	static CursorMode cursorMode = CursorMode::NORMAL;
	static bool disabled = false;

	static std::string keystring = "";
	static Vector2f mousePosition = Vector2f();
	static Vector2f mouseDelta = Vector2f();
	static Vector2f scrollDelta = Vector2f();

	static std::array<Vector2f, 20> mousePressPositions;

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

	const std::vector<TypeInput>& Input::getKeysTyped()
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
			typedKeys.push_back({ key, -1 });
		}
		if (action == GLFW_RELEASE) {
			releasedKeys.insert(key);
			downKeys.erase(key);
		}
		if (action == GLFW_REPEAT) {
			typedKeys.push_back({ key, -1 });
		}
	}


	void Input::handleCursor(float x, float y)
	{
		Vector2f newPosition(x, y);
		mouseDelta += newPosition - mousePosition;
		mousePosition = newPosition;

		if (cursorMode != CursorMode::GRABBED) {
			mousePosition = newPosition;
		}
		else {
			Engine::getWindow().setMousePosition(mousePosition.x, mousePosition.y);
		}

	}

	void Input::handleScroll(float x, float y)
	{
		scrollDelta += Vector2f(x, y);
	}

	void Input::handleTyped(unsigned int unicode)
	{
		//Oh bby lets lose some of that goodstuff input values and goodshit stuff dont even worry about it bby
		assert(typedKeys.size() > 0);
		typedKeys.push_back(typedKeys.back());
		typedKeys.back().unicode = (int)unicode;

		keystring += (char)unicode;
	}

	void Input::handleMouse(int button, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			pressedMouse.insert(button);
			downMouse.insert(button);
			mousePressPositions[button] = mousePosition;
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
		if (disabled)
			return true;

		for (const auto key : typedKeys) {
			if (key.keycode == keycode)
				return true;
		}
		return false;
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

	Vector2f Input::getMouseLastPressedPosition(int mb)
	{
		return mousePressPositions[mb];
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
