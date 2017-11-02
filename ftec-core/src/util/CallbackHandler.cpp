#include "CallbackHandler.h"

namespace ftec {
	CallbackHandle::CallbackHandle(CallbackHandler<void()>* h) : m_Handler(h) {}
	CallbackHandle::~CallbackHandle() { if(m_Handler) m_Handler->unregisterCallback(this); }
}
