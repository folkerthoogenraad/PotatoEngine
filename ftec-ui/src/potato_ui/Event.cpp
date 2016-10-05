#include "Event.h"

namespace potato {
	Event::Event(EventType type, std::shared_ptr<EventData> data)
		:m_Data(data), m_Type(type)
	{

	}
}