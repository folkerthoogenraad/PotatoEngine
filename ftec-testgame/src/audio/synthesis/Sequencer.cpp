#include "Sequencer.h"
#include "logger/log.h"

namespace ftec {
	Sequencer::Sequencer()
	{ }

	void Sequencer::setClock(AudioModuleOutput clock)
	{
		m_Clock.function = clock;
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
			bool up = m_Clock.buffer[i] >= 1;
			if (up != m_ClockState) {
				if (up) {
					m_Current++;
				}
				m_ClockState = up;
			}
			if (m_Current >= m_Notes.size())
				m_Current = 0;

			if (m_Current >= 0 && m_Notes.size() > 0)
				input[i] = m_Notes[m_Current  % m_Notes.size()];
			else
				input[i] = 0;
		}
	}
}
