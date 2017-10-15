#pragma once

#include "AudioModule.h"

namespace ftec {

	class Distortion {
	public:
		enum Mode {
			HardCab,
			Reflect
		};
	private:
		AudioInput m_Input;
		double m_Preamp = 1;
		double m_Postamp = 1;
		double m_Threshold = 1;
		Mode m_Mode;
	public:
		void setPreamp(double gain);
		void setPostamp(double gain);
		void setThreshold(double gain);

		void setMode(Mode mode);

		void setInput(AudioModuleOutput out);

		void out(std::vector<double> &input, AudioFormat format);
	};

}