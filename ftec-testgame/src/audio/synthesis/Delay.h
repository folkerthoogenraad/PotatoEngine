#pragma once

#include "AudioModule.h"
#include "audio/iir/IIRFilter.h"

namespace ftec {

	class Delay {
		std::vector<double> m_Memory;

		double m_DelayTime = 0.1;
		double m_Feedback = 0.5;

		double m_DelayCurrentTime = 0;

		IIRFilter m_Filter;
		bool m_UseFilter = false;
		double m_CutoffFrequency = 1000;

		AudioInput m_Input;
	public:
		Delay();

		void setUseFilter(bool use);
		void setFilterCutoff(double freq);

		void setDelayFrequency(double frequency);
		void setFeedback(double gain);

		void setInput(AudioModuleOutput input);

		void out(std::vector<double>& input, AudioFormat format);

	};


}