#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include <functional>

#include "math/math.h"
#include "audio\AudioSystem.h"
#include "audio\AudioBuffer.h"
#include "audio\AudioSource.h"
#include "audio\AudioUtils.h"
#include "audio\synthesis\ModularSystem.h"
#include "audio\synthesis\Oscillator.h"
#include "audio\synthesis\LowPassFilter.h"
#include "audio\synthesis\Clock.h"
#include "audio\synthesis\Envelope.h"

#include "math/math.h"

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

	auto system = std::make_shared<AudioSystem>(format);

	ModularSystem master(system);

	Oscillator osc;
	osc.setFrequency(110 / 3.0);
	osc.setWaveType(Oscillator::Square);
	osc.setAmplitude(toGain(-12.0));

	Oscillator modulator;
	modulator.setFrequency(0.5);
	modulator.setRange(0.6, 1);
	modulator.setWaveType(Oscillator::Sine);

	Clock clock;
	clock.setBPM(400);
	clock.setPulseLength(0.01);

	Envelope envelope;
	envelope.setAttack(0);
	envelope.setRelease(0.2);

	osc.setVCPulseWidth(MODULE_OUT(&Oscillator::out, &modulator));

	envelope.setGate(MODULE_OUT(&Clock::out, &clock));
	osc.setVCAmplitude(MODULE_OUT(&Envelope::out, &envelope));
	
	master.setInput(MODULE_OUT(&Oscillator::out, &osc));

	master.play();
	
	//debugWriteToPCM("audio.pcm", MODULE_OUT(&Oscillator::out, &osc), format, 10);
	

	WAIT();

	return 0;
}

