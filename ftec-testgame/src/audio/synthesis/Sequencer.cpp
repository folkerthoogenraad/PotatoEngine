#include "Sequencer.h"
#include "logger/log.h"
#include "math/math.h"
#include "audio/AudioUtils.h"

namespace ftec {
	Sequencer::Sequencer()
	{ }

	void Sequencer::setClock(AudioModuleOutput clock)
	{
		m_Clock.function = clock;
	}

	void Sequencer::setLegatoTime(double time)
	{
		m_LegatoTime = time;
	}

	void Sequencer::setRandomRange(double min, double max)
	{
		m_RandomRangeMin = min;
		m_RandomRangeMax = max;
	}

	void Sequencer::setRandomness(double random)
	{
		m_RandomChance = random;
	}

	void Sequencer::setCurrent(int note)
	{
		m_Current = note;
	}

	std::vector<double>& Sequencer::getNotes()
	{
		return m_Notes;
	}

	const std::vector<double>& Sequencer::getNotes() const
	{
		return m_Notes;
	}

	void Sequencer::out(std::vector<double>& input, AudioFormat format)
	{
		m_Clock.execute(format);

		for (int i = 0; i < input.size(); i++) {
			m_TimeSinceSwitch += 1.0 / format.getSampleRate();

			bool up = m_Clock.buffer[i] >= 1;
			
			if (up != m_ClockState) {
				if (up) {
					m_Current++;

					if (ftec::random() < m_RandomChance) {
						m_Notes[m_Current] = ftec::remap(0, 1, m_RandomRangeMin, m_RandomRangeMax, ftec::random());
					}

				}
				m_ClockState = up;
				m_TimeSinceSwitch = 0;
			}
			
			if (m_Current >= m_Notes.size())
				m_Current = 0;

			if (m_TimeSinceSwitch < m_LegatoTime && up) {
				int previousIndex = m_Current - 1;
				while (previousIndex < 0)
					previousIndex += m_Notes.size();

				double previous = m_Notes[previousIndex  % m_Notes.size()];
				double current = m_Notes[m_Current  % m_Notes.size()];

				input[i] = ftec::lerp(previous, current, m_TimeSinceSwitch / m_LegatoTime);
			}

			else if (m_Current >= 0 && m_Notes.size() > 0)
				input[i] = m_Notes[m_Current  % m_Notes.size()];
			else
				input[i] = 0;
		}
	}
}
