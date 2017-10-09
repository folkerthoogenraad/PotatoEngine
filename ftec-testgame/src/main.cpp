#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include <functional>

#include "math/math.h"
#include "audio\AudioSystem.h"
#include "audio\AudioClip.h"
#include "audio\AudioSource.h"
#include "audio\AudioUtils.h"

#include <climits>

#include <thread>

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	AudioFormat format(
		44100,
		16,
		AudioFormat::Mono
	);

	std::vector<double> data;

	for (int i = 0; i < format.getSampleRate() / 2; i++) {
		double frequency = 220;

		double timeInSeconds = i / (double)format.getSampleRate();

		double value = audioSawtooth(timeInSeconds * frequency);

		value *= toGain(-3.0);
		data.push_back(value);
	}

	auto system = std::make_shared<AudioSystem>(format);

	AudioSource source(system);
	AudioBuffer clip(system);

	clip.setDataNormalized(data, format);
	
	source.queueBuffer(clip);
	source.queueBuffer(clip);
	source.play();

	for (; true;) {
		LOG(source.getBuffersProcessed());

		if (source.getBuffersProcessed() > 0) {
			source.unqueueBuffer(clip);
			source.queueBuffer(clip);
		}

		using namespace std;
		using namespace chrono;

		this_thread::sleep_for(100ms);
	}

	WAIT();

	return 0;
}

