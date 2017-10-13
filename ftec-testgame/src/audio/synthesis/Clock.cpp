#include "Clock.h"

#include "logger/log.h"

namespace ftec {

	void Clock::setPulseLength(double percentage)
	{
		m_PulseLength = percentage;
	}

	void Clock::setBPM(double bpm)
	{
		m_BPM = bpm;
	}

	void Clock::out(std::vector<double>& data, AudioFormat format)
	{
		double secondsPerBeat = 1.0 / (m_BPM / 60.0);

		for (int i = 0; i < data.size(); i++) {
			m_Phase += 1.0 / format.getSampleRate();

			if (m_Phase >= secondsPerBeat)
				m_Phase -= secondsPerBeat;
			
			data[i] = 0;

			if (m_Phase <= m_PulseLength * secondsPerBeat)
				data[i] = 1;
		}
	}

}
