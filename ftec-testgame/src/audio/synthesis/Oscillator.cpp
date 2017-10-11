#include "Oscillator.h"
#include "audio\AudioUtils.h"
#include "logger/log.h"
#include "math/math.h"

#include <assert.h>

namespace ftec {
	Oscillator::Oscillator()
		: m_Phase(0), m_Type(WaveType::Sine), m_PulseWidth(1), m_Amplitude(1), m_Offset(0)
	{
	}

	void Oscillator::setFrequency(double freq)
	{
		m_Frequency = freq;
	}

	void Oscillator::setAmplitude(double amp)
	{
		m_Amplitude = amp;
	}

	void Oscillator::setPulseWidth(double width)
	{
		m_PulseWidth = width;
	}

	void Oscillator::setOffset(double offset)
	{
		m_Offset = offset;
	}

	void Oscillator::setRange(double min, double max)
	{
		m_Offset = (min + max) / 2.0;
		m_Amplitude = (max - min) / 2.0;
	}

	void Oscillator::setVCFrequency(AudioModuleOutput out)
	{
		m_VCPitch.function = out;
	}

	void Oscillator::setVCAmplitude(AudioModuleOutput out)
	{
		m_VCAmplitude.function = out;
	}

	void Oscillator::setVCPulseWidth(AudioModuleOutput out)
	{
		m_VCPulseWidth.function = out;
	}

	void Oscillator::setWaveType(WaveType type)
	{
		m_Type = type;
	}

	void Oscillator::out(std::vector<double>& data, AudioFormat format)
	{
		if (m_Frequency == 0)
			return;

		bool bwidth = m_VCPulseWidth.execute(format);
		bool bamp = m_VCAmplitude.execute(format);
		bool bpitch = m_VCPitch.execute(format);

		for (int i = 0; i < data.size(); i++) {
			double frequency = m_Frequency;
			double pulseWidth = m_PulseWidth;
			double amplitude = m_Amplitude;

			if (bwidth)
				pulseWidth *= m_VCPulseWidth.buffer[i];
			if (bamp)
				amplitude *= m_VCAmplitude.buffer[i];

			m_Phase += m_Frequency / (double)format.getSampleRate();

			double evalPoint = 1;
			
			//TODO negative pulseWidth
			if(pulseWidth != 0)
				evalPoint = ftec::clamp(0.0, 1.0, fmod(m_Phase, 1) / pulseWidth);


			double value = 0;
			
			switch (m_Type) {
			case WaveType::Sawtooth:
				value = audioSawtooth(evalPoint);
				break;
			case WaveType::Sine:
				value = audioSine(evalPoint);
				break;
			case WaveType::Square:
				value = audioSquare(evalPoint);
				break;
			case WaveType::Triangle:
				value = audioTriangle(evalPoint);
				break;
			default:
				assert(false);
				break;
			}

			value *= amplitude;

			data[i] = value + m_Offset;
		}
	}
}
