#include "CallbackHandler.h"

namespace ftec {
	CallbackHandle::CallbackHandle(CallbackHandler<void()>* h) : m_Handler(h) {}
	CallbackHandle::~CallbackHandle() { m_Handler->unregisterCallback(this); }
}
