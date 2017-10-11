#pragma once

//http://cmc.music.columbia.edu/MusicAndComputers/chapter4/04_09.php

#include <functional>
#include <vector>
#include <string>
#include "audio\AudioSystem.h"

#define MODULE_OUT(function, pointer) std::bind(function, pointer, std::placeholders::_1, std::placeholders::_2)

namespace ftec {
	typedef std::function<void(std::vector<double> &input, AudioFormat format)> AudioModuleOutput;

	struct AudioInput {
		AudioModuleOutput function;
		std::vector<double> buffer;

		AudioInput();
		bool execute(AudioFormat format);
	};


	void debugWriteToPCM(const std::string &filename, AudioModuleOutput function, AudioFormat format, double lengthInSeconds);
}