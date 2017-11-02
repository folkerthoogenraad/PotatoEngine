#pragma once

#include <map>
#include <functional>
#include <memory>
#include <vector>

// TODO think about memory and ownership,
// Currently this is pretty weird

namespace ftec {

	template <typename T>
	class CallbackHandler;

	class CallbackHandle;

	class CallbackHandle {
		CallbackHandler<void()>* m_Handler;

	public:
		CallbackHandle(CallbackHandler<void()> *h);
		~CallbackHandle();
	};

	template <typename T>
	class CallbackHandler {
		std::map<CallbackHandle*, std::function<T>> m_Callbacks;

	public:
		void unregisterCallback(CallbackHandle *v)
		{
			auto i = m_Callbacks.find(v);

			if (i == m_Callbacks.end())
				return;

			m_Callbacks.erase(i);
		}
		std::shared_ptr<CallbackHandle> registerCallback(std::function<T> func)
		{
			auto handle = std::make_shared<CallbackHandle>((CallbackHandler<void()>*)this);

			m_Callbacks[handle.get()] = func;

			return std::move(handle);
		}

		template <typename... Params>
		void invoke(Params&&... args)
		{
			for (auto i : m_Callbacks)
			{
				//TODO create custom invokers?
				(i.second)(std::forward<Params>(args)...);
			}
		}

		template <typename... Params>
		void operator()(Params&&... args)
		{
			invoke(std::forward<Params>(args)...);
		}

		std::shared_ptr<CallbackHandle> operator << (std::function<T> func) { return registerCallback(func); }

		std::shared_ptr<CallbackHandle> operator += (std::function<T> func) { return registerCallback(func); }
		std::shared_ptr<CallbackHandle> operator -= (CallbackHandle *v) { return unregisterCallback(v); }

		friend class CallbackHandle;
	};

	namespace callback {
		typedef std::shared_ptr<CallbackHandle> Handle;
		typedef std::vector<Handle> HandleList;
	}
}