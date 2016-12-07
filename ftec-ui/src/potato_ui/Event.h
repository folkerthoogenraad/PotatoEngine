#pragma once

#include <memory>

namespace potato {

	class PotatoUI;

	class Event {
	private:
		bool m_Consumed = false;
		std::shared_ptr<PotatoUI> m_UI;
	public:
		//Creates a new event from the given input values in ftec::Input
		Event(std::shared_ptr<PotatoUI> ui);
		~Event() = default;

		bool isConsumed() { return m_Consumed; }
		void consume() { m_Consumed = true; }

		void yield();
	};

}