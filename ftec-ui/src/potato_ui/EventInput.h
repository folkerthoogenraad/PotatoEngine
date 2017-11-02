#pragma once

#include <vector>
#include <functional>

namespace ftec {
	class Event;
}

namespace potato {

	
	class EventInput {
	private:
		std::vector<ftec::Event> m_Events;
	public:
		EventInput() { poll(); }

		void forEach(std::function<void(ftec::Event &evt)> function);
		
		std::vector<ftec::Event> &getEvents() { return m_Events; }; // ? const? maybe?
	private:
		void poll();
	};

}