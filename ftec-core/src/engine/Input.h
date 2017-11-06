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

	/**
	 * Input class.
	 * @see EngineContext
	*/
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
		/**
		 * Returns whether the given keycode is currently in the down state
		*/
		bool isKeyDown(int keycode) const;
		/**
		* Returns whether the given keycode is pressed in the last update(). Note: Repeated presses 
		* do not count as new presses in the Input class.
		*/
		bool isKeyPressed(int keycode) const;
		/**
		* Returns whether the given keycode is released in the last update().
		*/
		bool isKeyReleased(int keycode) const;

		/**
		* Returns whether the given mousebutton is currently in the down state
		*/
		bool isMouseButtonDown(int mousebutton) const;
		/**
		* Returns whether the given mousebutton is pressed in the last update().
		*/
		bool isMouseButtonPressed(int mousebutton) const;
		/**
		* Returns whether the given mousebutton is released in the last update().
		*/
		bool isMouseButtonReleased(int mousebutton) const;

		float getMouseX() const;
		float getMouseY() const;
		float getMouseDeltaX() const;
		float getMouseDeltaY() const;

		/**
		 * Returns the mouse position
		*/
		Vector2f getMousePosition() const;
		/**
		* Returns the mouse delta since the last update().
		*/
		Vector2f getMouseDelta() const;
		/**
		* Returns the mouse scroll delta since the last update().
		*/
		Vector2f getScroll() const;

		/**
		 * Updates the input state with the given events.
		*/
		void update(const std::vector<Event> &events);

		void setEnabled(bool e);
		bool isEnabled() const;

		/**
		 * Returns the string that was typed since the last update()
		*/
		const std::string &getKeyString() const;

		const std::set<int> &getKeysDown() const;
		const std::set<int> &getKeysPressed() const;
		const std::set<int> &getKeysReleased() const;
		const std::vector<int> &getKeysTyped() const;

		const std::set<int> &getMouseButtonsDown() const;
		const std::set<int> &getMouseButtonsPressed() const;
		const std::set<int> &getMouseButtonsReleased() const;

		/**
		 * Returns the events since the last update()
		*/
		const std::vector<Event> &getEvents() const;
	};
}