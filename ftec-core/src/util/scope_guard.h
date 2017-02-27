#pragma once


#include <functional>

namespace std {

	class scope_guard {
		std::function<void()> m_Function;
		bool m_Use;
	public:
		scope_guard(std::function<void()> func);
		~scope_guard();

		void cancel();
		void resume();
	};
}