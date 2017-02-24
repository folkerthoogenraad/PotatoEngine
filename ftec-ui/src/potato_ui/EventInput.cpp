#include "EventInput.h"

#include "Event.h"

#include "engine/Input.h"

namespace potato {

	void EventInput::poll()
	{
		using namespace ftec;

		//Empty the list
		m_Events.clear();

		//Create the base data for the event
		Event evt;

		evt.m_CrtlDown = Input::isKeyDown(KEY_LEFT_CONTROL) || Input::isKeyDown(KEY_RIGHT_CONTROL);
		evt.m_ShiftDown = Input::isKeyDown(KEY_LEFT_SHIFT) || Input::isKeyDown(KEY_RIGHT_SHIFT);
		evt.m_AltDown = Input::isKeyDown(KEY_LEFT_ALT) || Input::isKeyDown(KEY_RIGHT_ALT);

		evt.m_MousePosition = Input::getMousePosition();
		evt.m_MouseDelta = Input::getMouseDelta();


		//---------------------------------------------------------
		// Keyboard events
		//---------------------------------------------------------
		//Pressed events
		{
			evt.m_EventType = EventType::KEYBOARD_PRESSED;

			for (const auto &press : Input::getKeysPressed())
			{
				evt.m_KeyCode = press;

				m_Events.push_back(evt);
			}
		}
		//Release events
		{
			evt.m_EventType = EventType::KEYBOARD_RELEASED;

			for (const auto &release : Input::getKeysReleased())
			{
				evt.m_KeyCode = release;

				m_Events.push_back(evt);
			}
		}
		//Type events
		{
			evt.m_EventType = EventType::KEYBOARD_TYPED;

			for (const auto &type : Input::getKeysTyped()) // 
			{
				evt.m_KeyCode = type.keycode;
				evt.m_UnicodeKey = type.unicode;

				m_Events.push_back(evt);
			}
		}


		//---------------------------------------------------------
		// Mouse events
		//---------------------------------------------------------
		//Mouse pressed
		{
			evt.m_EventType = EventType::MOUSE_PRESSED;

			for (const auto &mb : Input::getMouseButtonsPressed())
			{
				evt.m_MouseButton = mb;
				evt.m_MouseStartPosition = Input::getMouseLastPressedPosition(mb);

				m_Events.push_back(evt);
			}
		}
		//Mouse released
		{
			evt.m_EventType = EventType::MOUSE_RELEASED;

			for (const auto &mb : Input::getMouseButtonsReleased())
			{
				evt.m_MouseButton = mb;
				evt.m_MouseStartPosition = Input::getMouseLastPressedPosition(mb);

				m_Events.push_back(evt);
			}
		}
		//Mouse drag
		{
			evt.m_EventType = EventType::MOUSE_DRAG;

			if (Input::getMouseDelta().sqrmagnitude() != 0) {
				for (const auto &mb : Input::getMouseButtonsDown()) {
					evt.m_MouseButton = mb;
					evt.m_MouseStartPosition = Input::getMouseLastPressedPosition(mb);

					m_Events.push_back(evt);
				}
			}
		}
		//Mouse move
		{
			evt.m_EventType = EventType::MOUSE_MOVE;

			if (Input::getMouseDelta().sqrmagnitude() != 0) {
				if (Input::getMouseButtonsDown().size() == 0) {
					m_Events.push_back(evt);
				}
			}
		}
	}

	void EventInput::forEach(std::function<void(Event &evt)> function)
	{
		for (auto &e : m_Events)
		{
			function(e);
		}
	}
}
