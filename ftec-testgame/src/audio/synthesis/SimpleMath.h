#pragma once

#include "AudioModule.h"

namespace ftec {
	class SimpleMath {
	private:
		std::vector<AudioInput> m_Inputs;

	public:
		void addAudioInput(AudioModuleOutput input);

		void out(std::vector<double>& data, AudioFormat format);
	};
}