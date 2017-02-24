#include "Event.h"
#include "engine/Input.h"
#include "PotatoUI.h"

namespace potato {

	Event::Event() : m_Consumed(false)
	{

	}

	std::ostream & operator<<(std::ostream & stream, EventType type)
	{
		switch (type) {
		case EventType::MOUSE_PRESSED: return stream << "MOUSE_PRESSED";
		case EventType::MOUSE_RELEASED: return stream << "MOUSE_RELEASED";
		case EventType::MOUSE_MOVE: return stream << "MOUSE_MOVE";
		case EventType::MOUSE_DRAG: return stream << "MOUSE_DRAG";

		case EventType::KEYBOARD_TYPED: return stream << "KEYBOARD_TYPED";
		case EventType::KEYBOARD_PRESSED: return stream << "KEYBOARD_PRESSED";
		case EventType::KEYBOARD_RELEASED: return stream << "KEYBOARD_RELEASED";
		}

		return stream;
	}
}