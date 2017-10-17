#pragma once

#include "AudioModule.h"

namespace ftec {

	class Delay {
		std::vector<double> m_Memory;

		double m_DelayTime = 0.1;
		double m_Feedback = 0.5;

		AudioInput m_Input;

		int m_CurrentIndex = 0;
	public:
		Delay();

		void setDelayTime(double timeInSeconds);
		void setFeedback(double gain);

		void setInput(AudioModuleOutput input);

		void out(std::vector<double>& input, AudioFormat format);

	};


}