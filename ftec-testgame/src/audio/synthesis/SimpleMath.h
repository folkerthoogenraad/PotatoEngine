#pragma once

#include "AudioModule.h"

namespace ftec {
	class SimpleMath {
	public:
		enum Operation{
			Add,
			Subtract,
			Multiply,
			Divide
		};
	private:
		std::vector<AudioInput> m_Inputs;
		Operation m_Operation = Multiply;
	public:
		void setOperation(Operation op);
		void addAudioInput(AudioModuleOutput input);

		void out(std::vector<double>& data, AudioFormat format);
	};
}