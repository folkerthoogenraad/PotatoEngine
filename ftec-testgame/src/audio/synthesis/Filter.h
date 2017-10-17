#pragma once

#include "AudioModule.h"
#include <complex>

namespace ftec {

	class Filter{
	public:
		enum FilterType {
			LowPass,
			HighPass,
			BandPass,
			Notch,
			Peak,
			LowShelf,
			HighShelf
		};
	private:
		AudioInput m_Input;

		FilterType m_Type = LowPass;
		double m_CutoffFrequency = 1000;
		double Q = 0.707;
		double m_PeakGain = 0.0;

		double time = 0;

	public:
		Filter();

		void setType(FilterType type);
		void setPeakGain(double db);
		void setCutoffFrequency(double frequency);
		void setQ(double q);

		void setInput(AudioModuleOutput out);

		void out(std::vector<double> &input, AudioFormat format);

	private:
		// Values for the actual Biquad filter
		void calcBiquad(FilterType type, double Fc, double Q, double peakGain);
		
		double a0 = 1;
		double a1 = 0;
		double a2 = 0;
		double b1 = 0;
		double b2 = 0;
		double z1 = 0;
		double z2 = 0;

		inline float process(float in) {
			double out = in * a0 + z1;
			z1 = in * a1 + z2 - b1 * out;
			z2 = in * a2 - b2 * out;
			return out;
		}
	};
}
