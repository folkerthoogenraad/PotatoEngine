#pragma once

#include <array>
#include "AudioModule.h"

namespace ftec {

	class Sequencer {
	private:
		std::vector<double> m_Notes;

		bool m_ClockState = false;
		int m_Current = 0;

		double m_TimeSinceSwitch = 0;
		double m_LegatoTime = 0;

		AudioInput m_Clock;
	public:
		Sequencer();

		void setClock(AudioModuleOutput clock);
		void setLegatoTime(double time);

		void setCurrent(int note);

		std::vector<double> &getNotes();
		const std::vector<double> &getNotes() const;

		void out(std::vector<double> &input, AudioFormat format);
	};

}