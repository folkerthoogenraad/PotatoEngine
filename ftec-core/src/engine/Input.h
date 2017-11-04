#pragma once

#include <set>
#include <string>
#include <vector>
#include "math/Vector2.h"

#include "Keycodes.h" //This is not needed, but its just better for everyone that uses input anyway. Will remove later on, probalby

namespace ftec {

	template <typename T>
	struct Vector2;
	typedef Vector2<float> Vector2f;

	class Event;

	enum class CursorMode {
		NORMAL, HIDDEN, GRABBED
	};

	class Input {
		std::set<int> downKeys = std::set<int>();
		std::set<int> pressedKeys = std::set<int>();
		std::set<int> releasedKeys = std::set<int>();

		std::vector<int> typedKeys = std::vector<int>();

		std::set<int> downMouse = std::set<int>();
		std::set<int> pressedMouse = std::set<int>();
		std::set<int> releasedMouse = std::set<int>();

		bool disabled = false;

		std::string keystring = "";
		Vector2f mousePosition = Vector2f();
		Vector2f mouseDelta = Vector2f();
		Vector2f scrollDelta = Vector2f();

		std::vector<Event> events;
	public:

		// Get key typed?
		bool isKeyDown(int keycode) const;
		bool isKeyPressed(int keycode) const;
		bool isKeyReleased(int keycode) const;

		bool isMouseButtonDown(int keycode) const;
		bool isMouseButtonPressed(int keycode) const;
		bool isMouseButtonReleased(int keycode) const;

		float getMouseX() const;
		float getMouseY() const;
		float getMouseDX() const;
		float getMouseDY() const;

		Vector2f getMousePosition() const;
		Vector2f getMouseDelta() const;
		Vector2f getScroll() const;

		void update(const std::vector<Event> &events);

		void setEnabled(bool e);
		bool isEnabled() const;

		const std::string &getKeyString() const;

		const std::set<int> &getKeysDown() const;
		const std::set<int> &getKeysPressed() const;
		const std::set<int> &getKeysReleased() const;
		const std::vector<int> &getKeysTyped() const;

		const std::set<int> &getMouseButtonsDown() const;
		const std::set<int> &getMouseButtonsPressed() const;
		const std::set<int> &getMouseButtonsReleased() const;

		const std::vector<Event> &getEvents() const;
	};
}