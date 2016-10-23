#pragma once

#include <vector>
#include <mutex>

namespace ftec {

	template <typename T>
	class PotatoQueue {
		std::vector<T> m_Data;
		std::mutex m_Mutex;

	public:
		PotatoQueue() = default;
		~PotatoQueue() = default;

		void push_back(T data) {
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_Data.push_back(std::move(data));
		}

		T pop_back() {
			std::lock_guard<std::mutex> lock(m_Mutex);
			
			//If this throws an exception, you might be fucked :)
			T b = m_Data.back();
			m_Data.pop_back();

			return std::move(b);
		}

		bool empty() {
			std::lock_guard<std::mutex> lock(m_Mutex);
			return m_Data.empty();
		}
	};
}