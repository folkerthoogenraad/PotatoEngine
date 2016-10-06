#pragma once
#include <memory>

namespace potato {

	class Event {
	private:
		bool m_Consumed = false;
	public:
		//Creates a new event from the given input values in ftec::Input
		Event();
		~Event() = default;

		bool isConsumed() { return m_Consumed; }
		void consume() { m_Consumed = true; }

	};

}