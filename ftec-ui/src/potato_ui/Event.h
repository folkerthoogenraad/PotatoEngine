#pragma once

#include <memory>

#include "math/Vector2.h"

namespace potato {

	enum EventType {
		MOUSE_PRESSED,
		MOUSE_RELEASED,
		MOUSE_MOVE,

		KEYBOARD_TYPED,
		KEYBOARD_PRESSED,
		KEYBOARD_RELEASED
	};

	class PotatoUI;

	class Event {
	private:
		bool m_Consumed = false;
		std::shared_ptr<PotatoUI> m_UI;

		EventType m_EventType;

		int m_KeyCode;
		int m_MouseButton;

		ftec::Vector2f m_MouseStartPosition; //Mouse Start Position
		ftec::Vector2f m_MousePosition; //Mouse Start Position
		ftec::Vector2f m_MouseDelta; //Mouse Start Position

		bool m_CrtlDown, m_ShiftDown, m_AltDown;
	public:
		//Creates a new event from the given input values in ftec::Input
		Event(std::shared_ptr<PotatoUI> ui);
		~Event() = default;

		bool isConsumed() const { return m_Consumed; }
		void consume() { m_Consumed = true; }

		EventType getType() const { return m_EventType; }

		bool isCrtlDown() const { return m_CrtlDown; };
		bool isShiftDown() const { return m_ShiftDown; };
		bool isAltDown() const { return m_AltDown; };
		bool isModifierDown() const { return isCrtlDown() || isAltDown() || isShiftDown(); };

		int getKeyCode() const { return m_KeyCode; }
		int getMouseButton() const { return m_MouseButton; }

		ftec::Vector2f getMouseStartPosition() const { return m_MouseStartPosition; }
		ftec::Vector2f getMouseCurrentPosition() const { return m_MousePosition; }
		ftec::Vector2f getMouseDelta() const { return m_MouseDelta; }

		operator bool() { return !m_Consumed; }

		friend PotatoUI;
	};

}