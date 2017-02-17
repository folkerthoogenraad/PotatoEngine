#pragma once

#include <vector>
#include <functional>

namespace potato {

	class Event;
	
	class EventInput {
	private:
		std::vector<Event> m_Events;
	public:
		EventInput() { poll(); }

		void forEach(std::function<void(Event &evt)> function);
		
		std::vector<Event> &getEvents() { return m_Events; }; // ? const? maybe?
	private:
		void poll();
	};

}