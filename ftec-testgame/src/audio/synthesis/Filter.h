#pragma once

#include "AudioModule.h"
#include <complex>

namespace ftec {

	class Filter{
		AudioInput m_Input;
		double m_Value = 0;
		double m_Amount = 0;

		std::vector<std::complex<double>> m_Buffer;
	public:
		Filter();

		void setInput(AudioModuleOutput out);

		void setAmount(double amount);
		
		void out(std::vector<double> &input, AudioFormat format);
	};
}
