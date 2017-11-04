#include "Input.h"

#include "Engine.h"

#include "graphics/GL.h"
#include "graphics/Window.h"

#include "math/Vector2.h"

#include <assert.h>
#include <array>

#include "logger/log.h"

namespace ftec {


	Vector2f Input::getMousePosition() const
	{
		return mousePosition;
	}

	Vector2f Input::getMouseDelta() const
	{
		return disabled ? Vector2f() : mouseDelta;
	}

	Vector2f Input::getScroll() const
	{
		return disabled ? Vector2f() : scrollDelta;
	}

	void Input::update(const std::vector<Event>& events)
	{
		pressedKeys.clear();
		releasedKeys.clear();
		typedKeys.clear();
		pressedMouse.clear();
		releasedMouse.clear();
		mouseDelta = Vector2f();
		scrollDelta = Vector2f();
		keystring = "";

		this->events = events;

		for (Event e : events) {
			switch (e.getType()) {
			case EventType::KEYBOARD_PRESSED:
				pressedKeys.insert(e.getKeyCode());
				downKeys.insert(e.getKeyCode());
				break;
			case EventType::KEYBOARD_RELEASED:
				releasedKeys.insert(e.getKeyCode());
				downKeys.erase(e.getKeyCode());
				break;
			case EventType::KEYBOARD_TYPED:
				typedKeys.push_back(e.getUnicodeKey());
				break;

			case EventType::MOUSE_MOVE:
			case EventType::MOUSE_DRAG:
				mousePosition = e.getMousePosition();
				mouseDelta += e.getMouseDelta();
				break;

			case EventType::MOUSE_PRESSED:
				releasedMouse.insert(e.getKeyCode());
				downMouse.insert(e.getKeyCode());
				break;
			case EventType::MOUSE_RELEASED:
				releasedMouse.insert(e.getKeyCode());
				downMouse.erase(e.getKeyCode());
				break;

			case EventType::MOUSE_SCROLL:
				scrollDelta += e.getScrollDirection();
				break;
				
			default:
				assert(false);
				break;
			}
		}
	}

	void Input::setEnabled(bool e)
	{
		disabled = !e;
	}

	bool Input::isEnabled() const
	{
		return !disabled;
	}

	const std::string & Input::getKeyString() const
	{
		return keystring;
	}

	const std::set<int>& Input::getKeysDown() const
	{
		return downKeys;
	}

	const std::set<int>& Input::getKeysPressed() const
	{
		return pressedKeys;
	}

	const std::set<int>& Input::getKeysReleased() const
	{
		return releasedKeys;
	}

	const std::vector<int>& Input::getKeysTyped() const
	{
		return typedKeys;
	}

	const std::set<int>& Input::getMouseButtonsDown() const
	{
		return downMouse;
	}

	const std::set<int>& Input::getMouseButtonsPressed() const
	{
		return pressedMouse;
	}

	const std::set<int>& Input::getMouseButtonsReleased() const
	{
		return releasedMouse;
	}

	const std::vector<Event>& Input::getEvents() const
	{
		return events;
	}

	bool Input::isKeyDown(int keycode) const
	{
		return !disabled && downKeys.find(keycode) != downKeys.end();
	}

	bool Input::isKeyPressed(int keycode) const
	{
		return !disabled && pressedKeys.find(keycode) != pressedKeys.end();
	}

	bool Input::isKeyReleased(int keycode) const
	{
		return !disabled && releasedKeys.find(keycode) != releasedKeys.end();
	}


	bool Input::isMouseButtonPressed(int keycode) const
	{
		return !disabled && pressedMouse.find(keycode) != pressedMouse.end();
	}

	bool Input::isMouseButtonDown(int keycode) const
	{
		return !disabled && downMouse.find(keycode) != downMouse.end();
	}

	bool Input::isMouseButtonReleased(int keycode) const
	{
		return !disabled && releasedMouse.find(keycode) != releasedMouse.end();
	}

	float Input::getMouseX() const
	{
		return mousePosition.x;
	}
	float Input::getMouseY() const
	{
		return mousePosition.y;
	}
	float Input::getMouseDX() const
	{
		return disabled ? 0 : mouseDelta.x;
	}
	float Input::getMouseDY() const
	{
		return disabled ? 0 : mouseDelta.y;
	}

}
