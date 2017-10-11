#include "LowPassFilter.h"

namespace ftec {
	void LowPassFilter::setInput(AudioModuleOutput out)
	{
		m_Input.function = out;
	}

	void LowPassFilter::setAmount(double amount)
	{
		m_Amount = amount;
	}

	void LowPassFilter::out(std::vector<double>& input, AudioFormat format)
	{
		if (!m_Input.function)
			return;

		m_Input.function(m_Input.buffer, format);

		double a = pow(2, m_Amount);

		for (int i = 0; i < input.size(); i++) {
			m_Value = (m_Value * (a - 1) + m_Input.buffer[i]) / a;
			input[i] = m_Value;
		}
	}
}
