#include "Filter.h"

#include "ModularSystem.h"
#include "audio/AudioUtils.h"

#include "logger/log.h"
#include "math/math.h"

namespace ftec {

	Filter::Filter()
	{
	}

	void Filter::setType(IIRFilter::FilterType type)
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

	void Filter::out(std::vector<double>& input, AudioFormat format)
	{
		if (!m_Input.function)
			return;

		m_Input.execute(format);

		// Calculate once because it does not change at the moment
		m_Filter.setFilter(m_Type, m_CutoffFrequency / format.getSampleRate(), Q, m_PeakGain);
		
		//calcBiquad(m_Type, m_CutoffFrequency / format.getSampleRate(), Q, m_PeakGain);

		for (int i = 0; i < input.size(); i++) {
			input[i] = m_Filter.process(m_Input.buffer[i]);
		}

	}
}
