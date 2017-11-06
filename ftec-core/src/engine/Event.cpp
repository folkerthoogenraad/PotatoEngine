#include "Event.h"

namespace ftec {

	Event::Event() : m_Consumed(false)
	{

	}

	std::ostream & operator<<(std::ostream & stream, EventType type)
	{
		switch (type) {
		case EventType::MousePressed: return stream << "MousePressed";
		case EventType::MouseReleased: return stream << "MouseReleased";
		case EventType::MouseMove: return stream << "MouseMove";
		case EventType::MouseDrag: return stream << "MouseDrag";

		case EventType::KeyboardTyped: return stream << "KeyboardTyped";
		case EventType::KeyboardPressed: return stream << "KeyboardPressed";
		case EventType::KeyboardReleased: return stream << "KeyboardReleased";
		}

		return stream;
	}
}