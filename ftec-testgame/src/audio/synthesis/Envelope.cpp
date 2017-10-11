#include "Envelope.h"

#include "math/math.h"

namespace ftec {
	void Envelope::setAttack(double timeInSeconds)
	{
		m_Attack = timeInSeconds;
	}
	void Envelope::setDecay(double timeInSeconds)
	{
		m_Decay = timeInSeconds;
	}
	void Envelope::setSustain(double factor)
	{
		m_Sustain = factor;
	}
	void Envelope::setRelease(double timeInSeconds)
	{
		m_Release = timeInSeconds;
	}
	void Envelope::setGate(AudioModuleOutput gate)
	{
		m_Gate.function = gate;
	}

	void Envelope::out(std::vector<double>& data, AudioFormat format)
	{
		m_Gate.execute(format);

		for (int i = 0; i < data.size(); i++) {
			m_Time += 1.0 / format.getSampleRate();

			bool open = m_Gate.buffer[i] >= 1;

			double volume = 0;

			if (open != m_Open) {
				m_Open = open;
				m_Time = 0;
				m_StartVolume = m_CurrentVolume;
			}

			if (open) {
				if (m_Time < m_Attack) {
					volume = lerp(m_StartVolume, 1.0, m_Time / m_Attack);
				}
				else if (m_Time - m_Attack < m_Decay) {
					volume = lerp(1.0, m_Sustain, (m_Time - m_Attack) / m_Decay);
				}
				else {
					volume = m_Sustain;
				}
			}
			
			if (!open) {
				if (m_Time < m_Release) {
					volume = (1 - m_Time / m_Release) * m_StartVolume;
				}
				else {
					volume = 0;
				}
			}

			m_CurrentVolume = volume;
			data[i] = volume;
		}
	}
}
