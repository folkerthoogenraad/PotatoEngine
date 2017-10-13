#include "Distortion.h"

#include "math/math.h"

namespace ftec {

	void Distortion::setPreamp(double gain)
	{
		m_Preamp = gain;
	}

	void Distortion::setPostamp(double gain)
	{
		m_Postamp = gain;
	}

	void Distortion::setThreshold(double gain)
	{
		m_Threshold = gain;
	}

	void Distortion::setInput(AudioModuleOutput out)
	{
		m_Input.function = out;
	}

	void Distortion::out(std::vector<double>& input, AudioFormat format)
	{
		m_Input.execute(format);

		for (int i = 0; i < input.size(); i++) {
			double v = m_Input.buffer[i];

			v *= m_Preamp;

			if (abs(v) > m_Threshold)
				v = sign(v) * m_Threshold;

			v *= m_Postamp;

			input[i] = v;
		}
	}
}