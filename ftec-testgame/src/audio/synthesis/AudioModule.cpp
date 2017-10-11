#include "AudioModule.h"
#include "ModularSystem.h"

#include "math/math.h"

#include <fstream>

namespace ftec {
	AudioInput::AudioInput()
	{
		buffer.resize(MODULAR_BUFFER_SIZE);
		std::fill(buffer.begin(), buffer.end(), 0);
	}
	bool AudioInput::execute(AudioFormat format)
	{
		if (!function)
			return false;

		function(buffer, format);
		return  true;
	}

	void debugWriteToPCM(const std::string & filename, AudioModuleOutput function, AudioFormat format, double lengthInSeconds)
	{
		std::ofstream writeFile;
		writeFile.open(filename, std::ios_base::out | std::ios_base::binary);
		writeFile.imbue(std::locale::classic());
		writeFile << std::ios::binary;

		std::vector<double> input;
		input.resize(MODULAR_BUFFER_SIZE);

		for (int i = 0; i < format.getSampleRate() * lengthInSeconds; i += MODULAR_BUFFER_SIZE) {
			function(input, format);

			//TODO check this
			for (size_t i = 0; i < input.size(); i++) {
				short v = (short)clamp((double)SHRT_MIN, (double)SHRT_MAX, (input[i]) * (double)SHRT_MAX);
				writeFile.put(v);
				writeFile.put(v >> 8);
			}

		}

		writeFile.close();
	}
}
