#pragma once

#include <assert.h>

namespace std {

	template <typename T>
	class not_null {
	private:
		T *m_Data;
	public:
		not_null(T *d) :m_Data(std::move(d)) { assert(m_Data != nullptr); };

		T* operator->() { return m_Data; };
		T& operator*() { return &m_Data; };
	};
}