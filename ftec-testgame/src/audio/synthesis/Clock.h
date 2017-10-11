#pragma once

#include "AudioModule.h"

namespace ftec {
	class Clock {
	private:
		double m_PulseLength = 0.05;
		double m_BPM = 100;

		double m_Phase = 0;
	public:

		void setPulseLength(double seconds);
		void setBPM(double bpm);
		
		void out(std::vector<double>& data, AudioFormat format);
	};
}