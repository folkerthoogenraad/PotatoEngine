#include "Delay.h"

namespace ftec {

	Delay::Delay() 
	{
		m_Memory.resize(48000);
	}
	
	void Delay::setDelayTime(double timeInSeconds)
	{
		m_DelayTime = timeInSeconds;
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

		size_t maxCurrent = m_DelayTime * format.getSampleRate();
		
		for (int i = 0; i < input.size(); i++) {
			double mem = m_Memory[m_CurrentIndex] * m_Feedback;
			double res = m_Input.buffer[i] + mem;

			input[i] = res;
			m_Memory[m_CurrentIndex] = res;

			m_CurrentIndex++;
			m_CurrentIndex = m_CurrentIndex % m_Memory.size();
			if (m_CurrentIndex > maxCurrent)
				m_CurrentIndex = 0;
		}
	}

}
