#include "Delay.h"

#include "logger/log.h"

namespace ftec {

	Delay::Delay() 
	{
		m_Memory.resize(48000);
		std::fill(m_Memory.begin(), m_Memory.end(), 0);
	}

	void Delay::setUseFilter(bool use)
	{
		m_UseFilter = use;
	}

	void Delay::setFilterCutoff(double freq)
	{
		m_CutoffFrequency = freq;
	}
	
	void Delay::setDelayFrequency(double timeInSeconds)
	{
		m_DelayTime = 1.0 / timeInSeconds;
	}

	void Delay::setFeedback(double gain)
	{
		m_Feedback = gain;
	}

	void Delay::setInput(AudioModuleOutput input)
	{
		m_Input.function = input;
	}

	void Delay::out(std::vector<double>& input, AudioFormat format)
	{
		m_Input.execute(format);

		double maxCurrent = m_DelayTime * format.getSampleRate();

		if (m_UseFilter)
			m_Filter.setFilter(IIRFilter::LowPass, m_CutoffFrequency / format.getSampleRate(), 0.707, 0);

		for (int i = 0; i < input.size(); i++) {
			size_t currentIndex = (size_t) (m_DelayCurrentTime) % m_Memory.size();

			double mem = m_Memory[currentIndex] * m_Feedback;
			
			//if (m_UseFilter) {
			//	mem = m_Filter.process(mem);
			//}

			double res = m_Input.buffer[i] + mem;

			if (m_UseFilter) {
				res = m_Filter.process(res);
			}

			input[i] = res;
			m_Memory[currentIndex] = res;

			m_DelayCurrentTime++;
			if (m_DelayCurrentTime > maxCurrent)
				m_DelayCurrentTime -= maxCurrent;
		}
	}

}
