#pragma once

#include "AudioModule.h"

namespace ftec {
	class Clock {
	private:
		double m_PulseLength = 0.5;
		double m_BPM = 100;

		double m_Phase = 0;
	public:

		//Pulse length in percentage of BPM (0 - 1)
		void setPulseLength(double percentage);
		void setBPM(double bpm);
		
		void out(std::vector<double>& data, AudioFormat format);
	};
}