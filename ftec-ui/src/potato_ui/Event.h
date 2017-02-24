#pragma once

#include <memory>
#include <iostream>

#include "math/Vector2.h"

namespace potato {

	enum class EventType {
		MOUSE_PRESSED		= 0x00,
		MOUSE_RELEASED		= 0x01,
		MOUSE_MOVE			= 0x02,
		MOUSE_DRAG			= 0x04,

		KEYBOARD_TYPED		= 0x08,
		KEYBOARD_PRESSED	= 0x10,
		KEYBOARD_RELEASED	= 0x20
	};

	std::ostream &operator <<(std::ostream &stream, EventType type);

	class Event {
	private:
		bool m_Consumed = false;

		EventType m_EventType;

		int m_KeyCode;
		int m_MouseButton;

		ftec::Vector2f m_MouseStartPosition; //Mouse Start Position
		ftec::Vector2f m_MousePosition; //Mouse Start Position
		ftec::Vector2f m_MouseDelta; //Mouse Start Position

		bool m_CrtlDown, m_ShiftDown, m_AltDown;
	public:
		Event();
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
		ftec::Vector2f getMousePosition() const { return m_MousePosition; }
		ftec::Vector2f getMouseDelta() const { return m_MouseDelta; }

		operator bool() { return !m_Consumed; }

		friend class EventInput;
	};

}