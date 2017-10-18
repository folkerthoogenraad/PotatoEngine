#include "SimpleMath.h"

#include <assert.h>

namespace ftec {
	void SimpleMath::setOperation(Operation op)
	{
		m_Operation = op;
	}
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
				switch (m_Operation) {
				case Operation::Add:
					data[i] += m_Inputs[j].buffer[i];
					break;
				case Operation::Subtract:
					data[i] -= m_Inputs[j].buffer[i];
					break;
				case Operation::Multiply:
					data[i] *= m_Inputs[j].buffer[i];
					break;
				case Operation::Divide: //Dangerous stuff right here
					data[i] /= m_Inputs[j].buffer[i];
					break;
				default:
					assert(false);
				}
			}
		}
	}

}
