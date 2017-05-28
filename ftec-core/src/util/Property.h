#pragma once

#include "CallbackHandler.h"

namespace ftec {

	template <typename T>
	class Property;

	template <typename T>
	class PropertyModifier {
		Property<T> *m_Property;
		bool m_Modified;

		PropertyModifier(Property<T> *v) : m_Property(v), m_Modified(false){};
	public:
		PropertyModifier(const PropertyModifier<T>&) = delete;

		PropertyModifier(PropertyModifier<T> && other) 
		{ 
			m_Property = other.m_Property;
			m_Modified = other.m_Modified;

			other.m_Modified = false;
		}

		~PropertyModifier() 
		{
			if (!m_Modified)
				return;

			m_Property->commit(); 
		}

		const T *operator->() const { return m_Property->m_Value; }
		const T &operator*() const { return *(m_Property->m_Value); }

		T *operator->() { m_Modified = true; return &m_Property->m_Value; }
		T &operator*() { m_Modified = true; return m_Property->m_Value; }

		friend Property<T>;
	};
	
	template <typename T>
	class Property {
		T m_Value;
		mutable CallbackHandler<void(const T&)> m_Callbacks;
	public:
		Property(T t) : m_Value(std::move(t)) {};
		Property(T &&t) : m_Value(std::move(t)) {};
		Property() : m_Value() {};

		const T *operator->() const { return &m_Value; }
		const T &operator*() const { return m_Value; }

		const T &get() const { return m_Value; }

		PropertyModifier<T> modify() { return std::move(this); }

		inline callback::Handle registerCallback(std::function<void(const T&)> value) const { return m_Callbacks.registerCallback(value); }
		inline callback::Handle operator<<(std::function<void(const T&)> value) const { return registerCallback(std::move(value)); }

		template <typename S>
		inline Property<T> &operator=(const S &other)
		{
			m_Value = other;

			commit();

			return *this;
		}

	private:
		void commit()
		{
			m_Callbacks(m_Value);
		}
		
		friend PropertyModifier<T>;
	};

}