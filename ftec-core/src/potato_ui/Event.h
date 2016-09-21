#pragma once
#include <memory>

namespace potato {

	enum class EventType {
		MOUSE_CLICK,
		MOUSE_MOVE,
		KEYBOARD_PRESS,
	};

	class EventData {
	public:
		EventData() = delete;
		virtual ~EventData() = default;
	};

	class Event {
	private:
		std::shared_ptr<EventData> m_Data;
		EventType m_Type;
	public:
		Event(EventType type, std::shared_ptr<EventData> data);
		~Event() = default;

		template<typename T>
		std::shared_ptr<T> getData()
		{
			return std::dynamic_pointer_cast<T>(m_Data);
		}

		EventType getType() { return m_Type; }
	};

}