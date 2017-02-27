#include "scope_guard.h"
namespace std {
	scope_guard::scope_guard(std::function<void()> func)
		: m_Function(func), m_Use(true)
	{

	}

	scope_guard::~scope_guard()
	{
		if (m_Use){
			m_Function();
		}
	}

	void scope_guard::cancel()
	{
		m_Use = false;
	}
	void scope_guard::resume()
	{
		m_Use = true;
	}
}
