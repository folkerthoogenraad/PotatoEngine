#pragma once

#include <memory>
#include <iostream>

#include "math/Vector2.h"

namespace ftec {

	enum class EventType {
		// I'm really not sure why these are powers of two :')
		MOUSE_PRESSED		= 1 << 0,
		MOUSE_RELEASED		= 1 << 1,
		MOUSE_MOVE			= 1 << 2,
		MOUSE_DRAG			= 1 << 3,
		MOUSE_SCROLL		= 1 << 4,

		KEYBOARD_TYPED		= 1 << 5,
		KEYBOARD_PRESSED	= 1 << 6,
		KEYBOARD_RELEASED	= 1 << 7
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

		float m_ScrollDirection;

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


		bool isMotionEvent() const { return m_EventType == EventType::MOUSE_DRAG || m_EventType == EventType::MOUSE_MOVE; }

		int getKeyCode() const { return m_KeyCode; }
		int getMouseButton() const { return m_MouseButton; }

		Vector2f getMouseStartPosition() const { return m_MouseStartPosition; }
		Vector2f getMousePosition() const { return m_MousePosition; }
		Vector2f getMouseDelta() const { return m_MouseDelta; }
		
		float getScrollDirection() const { return m_ScrollDirection; }

		int getUnicodeKey() { return m_UnicodeKey; }
		bool hasUnicodeKey() { return m_UnicodeKey > 0; }

		operator bool() { return !m_Consumed; }
	};

}