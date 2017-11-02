#include "Oscillator.h"
#include "audio\AudioUtils.h"
#include "logger/log.h"
#include "math/math.h"

#include <assert.h>

namespace ftec {
	Oscillator::Oscillator()
		: m_Type(WaveType::Sine), m_PulseWidth(1), m_Amplitude(1), m_Offset(0)
	{
		m_UnisonPhases[0] = 0;
		for (int i = 1; i < m_UnisonPhases.size(); i++) {
			m_UnisonPhases[i] = (double)rand() / (double)(RAND_MAX);
		}
		m_Harmonics[0] = 1;
		for (int i = 1; i < m_Harmonics.size(); i++) {
			m_Harmonics[i] = 0;
		}
	}

	void Oscillator::setHarmonic(int harmonic, double value)
	{
		m_Harmonics[harmonic] = value;
	}

	void Oscillator::setUnisonBlend(double blend)
	{
		m_UnisonBlend = blend;
	}

	void Oscillator::setUnisonDetune(double detune)
	{
		m_UnisonDetune = detune;
	}

	void Oscillator::setUnisonVoices(int unison)
	{
		m_UnisonVoices = ftec::clamp(1, 16, unison);
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
			if (bpitch)
				frequency *= m_VCPitch.buffer[i];

			double a = frequency / (double)format.getSampleRate();
			double output = 0;

			double totalMultiplier = 0;

			for (int i = 0; i < m_UnisonVoices; i++) {

				bool center = true;

				if (m_UnisonVoices > 1) {
					double cAmount = (i / (double)(m_UnisonVoices - 1)) * 2 - 1;
					
					if (m_UnisonVoices % 2 == 1) {
						// 3 voices, the center one will be 1 (0 1 2)
						center = i == m_UnisonVoices / 2;
					}
					else {
						// 4 voices, the center will be either 1 or 2 (0 1 2 3)
						center = i == m_UnisonVoices / 2 || i == m_UnisonVoices / 2 + 1;
					}

					double cUni = semitonesMultiplier(m_UnisonDetune * cAmount);// pow(2, (m_UnisonDetune * cAmount) / 12.0);

					//Detune is in semitones
					m_UnisonPhases[i] += a * cUni;
				}
				else {
					m_UnisonPhases[i] += a;
				}

				double evalPoint = 1;

				//TODO negative pulseWidth
				if (pulseWidth != 0)
					evalPoint = ftec::clamp(0.0, 1.0, fmod(m_UnisonPhases[i], 1) / pulseWidth);

				double value = 0; 
				double harmonicsDiv = 0;

				for (int i = 0; i < m_Harmonics.size(); i++) {
					double p = evalPoint * (i + 1);
					harmonicsDiv += m_Harmonics[i];
					switch (m_Type) {
					case WaveType::Sawtooth:
						value += audioSawtooth(p) * m_Harmonics[i];
						break;
					case WaveType::Sine:
						value += audioSine(p) * m_Harmonics[i];
						break;
					case WaveType::HalfSine:
						value += audioHalfSine(p) * m_Harmonics[i];
						break;
					case WaveType::Square:
						value += audioSquare(p) * m_Harmonics[i];
						break;
					case WaveType::Triangle:
						value += audioTriangle(p) * m_Harmonics[i];
						break;
					case WaveType::Noise:
						value += (random() * 2 - 1) * m_Harmonics[i];
						break;
					default:
						assert(false);
						break;
					}
				}
				value /= harmonicsDiv;

				if (!center) {
					value *= m_UnisonBlend;
					totalMultiplier += m_UnisonBlend;
				}
				else {
					totalMultiplier += 1;
				}

				output += value;
			}

			//I think
			output /= totalMultiplier;

			output *= amplitude;

			data[i] = output + m_Offset;
		}
	}
}
