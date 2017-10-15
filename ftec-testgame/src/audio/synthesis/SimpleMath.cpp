#include "SimpleMath.h"

namespace ftec {
	void SimpleMath::addAudioInput(AudioModuleOutput input)
	{
		m_Inputs.emplace_back();
		m_Inputs.back().function = input;
	}
	void SimpleMath::out(std::vector<double>& data, AudioFormat format)
	{
		if (m_Inputs.size() == 0)
			return;

		for (int j = 0; j < m_Inputs.size(); j++) {
			m_Inputs[j].execute(format);
		}
		for (int i = 0; i < data.size(); i++) {
			data[i] = m_Inputs[0].buffer[i];

			for (int j = 1; j < m_Inputs.size(); j++) {
				data[i] *= m_Inputs[j].buffer[i];
			}
		}
	}

}
