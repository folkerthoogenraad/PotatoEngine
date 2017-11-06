#pragma once

#include <memory>
#include <iostream>

#include "math/Vector2.h"

namespace ftec {

	enum class EventType {
		// I'm really not sure why these are powers of two :')
		MousePressed		= 1 << 0,
		MouseReleased		= 1 << 1,
		MouseMove			= 1 << 2,
		MouseDrag			= 1 << 3,
		MouseScroll			= 1 << 4,

		KeyboardTyped		= 1 << 5,
		KeyboardPressed	= 1 << 6,
		KeyboardReleased	= 1 << 7
	};

	std::ostream &operator <<(std::ostream &stream, EventType type);

	class Event {
	public:
		bool m_Consumed = false;

		EventType m_EventType;

		int m_UnicodeKey;
		int m_KeyCode;
		int m_MouseButton;

		Vector2f m_MouseStartPosition; //Mouse Start Position
		Vector2f m_MousePosition; //Mouse Start Position
		Vector2f m_MouseDelta; //Mouse Start Position

		Vector2f m_ScrollDirection;

		bool m_CrtlDown, m_ShiftDown, m_AltDown;
		bool m_Repeat = false;
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

		bool isRepeated() const { return m_Repeat; }

		bool isMotionEvent() const { return m_EventType == EventType::MouseDrag || m_EventType == EventType::MouseMove; }

		int getKeyCode() const { return m_KeyCode; }
		int getMouseButton() const { return m_MouseButton; }

		Vector2f getMouseStartPosition() const { return m_MouseStartPosition; }
		Vector2f getMousePosition() const { return m_MousePosition; }
		Vector2f getMouseDelta() const { return m_MouseDelta; }
		
		Vector2f getScrollDirection() const { return m_ScrollDirection; }

		int getUnicodeKey() { return m_UnicodeKey; }
		bool hasUnicodeKey() { return m_UnicodeKey > 0; }

		operator bool() { return !m_Consumed; }
	};

}