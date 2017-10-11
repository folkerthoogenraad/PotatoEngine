#pragma once

#include "ModularSystem.h"
#include "AudioModule.h"

namespace ftec {
	
	class Oscillator {
	public:
		enum WaveType {
			Sine,
			Square,
			Triangle,
			Sawtooth,
		};
	private:
		AudioInput m_VCPitch;
		AudioInput m_VCAmplitude;
		AudioInput m_VCPulseWidth;

		WaveType m_Type;

		double m_Amplitude;
		double m_Frequency;
		double m_Phase;
		double m_PulseWidth;
		
		double m_Offset;
	public:
		Oscillator();

		void setFrequency(double freq);
		void setAmplitude(double amp);
		void setPulseWidth(double width);
		void setOffset(double offset);
		void setRange(double min, double max);

		void setVCFrequency(AudioModuleOutput out);
		void setVCAmplitude(AudioModuleOutput out);
		void setVCPulseWidth(AudioModuleOutput out);

		void setWaveType(WaveType type);

		void out(std::vector<double> &input, AudioFormat format);
	};

}