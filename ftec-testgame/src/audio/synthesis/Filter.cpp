#include "Filter.h"

#include "ModularSystem.h"
#include "audio/AudioUtils.h"

#include "logger/log.h"
#include "math/math.h"

namespace ftec {

	Filter::Filter()
	{
	}

	void Filter::setType(FilterType type)
	{
		m_Type = type;
	}

	void Filter::setPeakGain(double db)
	{
		m_PeakGain = db;
	}

	void Filter::setCutoffFrequency(double frequency)
	{
		m_CutoffFrequency = frequency;
	}

	void Filter::setQ(double q)
	{
		Q = q;
	}

	void Filter::setInput(AudioModuleOutput out)
	{
		m_Input.function = out;
	}

	double time = 0;

	void Filter::out(std::vector<double>& input, AudioFormat format)
	{
		if (!m_Input.function)
			return;

		m_Input.execute(format);

		// Calculate once because it does not change at the moment
		calcBiquad(m_Type, m_CutoffFrequency / format.getSampleRate(), Q, m_PeakGain);

		for (int i = 0; i < input.size(); i++) {
			input[i] = process(m_Input.buffer[i]);
		}

	}
	// All credit goes to
	// http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
	void Filter::calcBiquad(FilterType type, double Fc, double Q, double peakGain)
	{
		double norm;
		double V = pow(10, fabs(peakGain) / 20.0);
		double K = tan(PI * Fc);

		switch (type) {
		case FilterType::LowPass:
			norm = 1 / (1 + K / Q + K * K);
			a0 = K * K * norm;
			a1 = 2 * a0;
			a2 = a0;
			b1 = 2 * (K * K - 1) * norm;
			b2 = (1 - K / Q + K * K) * norm;
			break;

		case FilterType::HighPass:
			norm = 1 / (1 + K / Q + K * K);
			a0 = 1 * norm;
			a1 = -2 * a0;
			a2 = a0;
			b1 = 2 * (K * K - 1) * norm;
			b2 = (1 - K / Q + K * K) * norm;
			break;

		case FilterType::BandPass:
			norm = 1 / (1 + K / Q + K * K);
			a0 = K / Q * norm;
			a1 = 0;
			a2 = -a0;
			b1 = 2 * (K * K - 1) * norm;
			b2 = (1 - K / Q + K * K) * norm;
			break;

		case FilterType::Notch:
			norm = 1 / (1 + K / Q + K * K);
			a0 = (1 + K * K) * norm;
			a1 = 2 * (K * K - 1) * norm;
			a2 = a0;
			b1 = a1;
			b2 = (1 - K / Q + K * K) * norm;
			break;

		case FilterType::Peak:
			if (peakGain >= 0) {    // boost
				norm = 1 / (1 + 1 / Q * K + K * K);
				a0 = (1 + V / Q * K + K * K) * norm;
				a1 = 2 * (K * K - 1) * norm;
				a2 = (1 - V / Q * K + K * K) * norm;
				b1 = a1;
				b2 = (1 - 1 / Q * K + K * K) * norm;
			}
			else {    // cut
				norm = 1 / (1 + V / Q * K + K * K);
				a0 = (1 + 1 / Q * K + K * K) * norm;
				a1 = 2 * (K * K - 1) * norm;
				a2 = (1 - 1 / Q * K + K * K) * norm;
				b1 = a1;
				b2 = (1 - V / Q * K + K * K) * norm;
			}
			break;
		case FilterType::LowShelf:
			if (peakGain >= 0) {    // boost
				norm = 1 / (1 + sqrt(2) * K + K * K);
				a0 = (1 + sqrt(2 * V) * K + V * K * K) * norm;
				a1 = 2 * (V * K * K - 1) * norm;
				a2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
				b1 = 2 * (K * K - 1) * norm;
				b2 = (1 - sqrt(2) * K + K * K) * norm;
			}
			else {    // cut
				norm = 1 / (1 + sqrt(2 * V) * K + V * K * K);
				a0 = (1 + sqrt(2) * K + K * K) * norm;
				a1 = 2 * (K * K - 1) * norm;
				a2 = (1 - sqrt(2) * K + K * K) * norm;
				b1 = 2 * (V * K * K - 1) * norm;
				b2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
			}
			break;
		case FilterType::HighShelf:
			if (peakGain >= 0) {    // boost
				norm = 1 / (1 + sqrt(2) * K + K * K);
				a0 = (V + sqrt(2 * V) * K + K * K) * norm;
				a1 = 2 * (K * K - V) * norm;
				a2 = (V - sqrt(2 * V) * K + K * K) * norm;
				b1 = 2 * (K * K - 1) * norm;
				b2 = (1 - sqrt(2) * K + K * K) * norm;
			}
			else {    // cut
				norm = 1 / (V + sqrt(2 * V) * K + K * K);
				a0 = (1 + sqrt(2) * K + K * K) * norm;
				a1 = 2 * (K * K - 1) * norm;
				a2 = (1 - sqrt(2) * K + K * K) * norm;
				b1 = 2 * (K * K - V) * norm;
				b2 = (V - sqrt(2 * V) * K + K * K) * norm;
			}
			break;
		}

		return;
	}
}
