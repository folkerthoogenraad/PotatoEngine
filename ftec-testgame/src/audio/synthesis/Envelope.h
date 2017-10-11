#pragma once

#include "AudioModule.h"

namespace ftec {
	class Envelope {
	private:
		double m_Attack = 0;
		double m_Decay = 0;
		double m_Sustain = 1;
		double m_Release = 0;

		double m_StartVolume = 0;
		double m_CurrentVolume = 0;
		double m_Time = 0;
		bool m_Open = false;

		AudioInput m_Gate;
	public:

		void setAttack(double timeInSeconds);
		void setDecay(double timeInSeconds);
		void setSustain(double factor);
		void setRelease(double timeInSeconds);

		void setGate(AudioModuleOutput gate);

		void out(std::vector<double> &input, AudioFormat format);
	};
}