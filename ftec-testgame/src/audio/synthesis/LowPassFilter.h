#pragma once

#include "AudioModule.h"

namespace ftec {

	class LowPassFilter{
		AudioInput m_Input;
		double m_Value = 0;
		double m_Amount = 0;
	public:
		void setInput(AudioModuleOutput out);

		void setAmount(double amount);
		
		void out(std::vector<double> &input, AudioFormat format);
	};
}
