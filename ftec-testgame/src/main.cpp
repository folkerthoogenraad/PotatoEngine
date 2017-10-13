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
#include "audio\synthesis\Distortion.h"
#include "audio\synthesis\Sequencer.h"

#include "math/math.h"

#include <climits>

#include <thread>

void test() 
{
	using namespace ftec;

	AudioFormat format(
		44100,
		16,
		AudioFormat::Mono
	);

	Oscillator osc;
	osc.setFrequency(220 / 4);
	osc.setWaveType(Oscillator::Sine);

	Oscillator modulator;
	modulator.setFrequency(0.5);
	modulator.setRange(0.2, 1);
	modulator.setWaveType(Oscillator::Sine);

	Clock clock;
	clock.setBPM(400);
	clock.setPulseLength(0.01);

	Envelope envelope;
	envelope.setAttack(0);
	envelope.setSustain(1);
	envelope.setDecay(0);
	envelope.setRelease(0.2);

	//osc.setVCPulseWidth(MODULE_OUT(&Oscillator::out, &modulator));

	envelope.setGate(MODULE_OUT(&Clock::out, &clock));
	osc.setVCAmplitude(MODULE_OUT(&Envelope::out, &envelope));

	std::vector<double> data;
	data.resize(MODULAR_BUFFER_SIZE);

	int times = 1000;

	LOG("Starting...");
	auto time = std::chrono::system_clock::now();
	
	for(int i = 0; i < times; i++)
		osc.out(data, format);

	auto end = std::chrono::system_clock::now();

	std::chrono::microseconds mss = std::chrono::duration_cast<std::chrono::microseconds>(end - time);
	double ms = (double)mss.count() / 1000.0;

	LOG(times << " times took " << ms << "ms");
	LOG("That is approximatly " << ms / times << "ms per loop");
	LOG("The buffer length is " << ((double)MODULAR_BUFFER_SIZE / (double)format.getSampleRate()) * 1000.0 << "ms");
}

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	AudioFormat format(
		44100,
		16,
		AudioFormat::Mono
	);

	//test();

	auto system = std::make_shared<AudioSystem>(format);

	ModularSystem master(system);

	const double base = 220;
	const double bpm = 128;
	const double subdivisions = 4;

	Oscillator osc;
	osc.setFrequency(base / 2);
	osc.setWaveType(Oscillator::Sawtooth);
	osc.setAmplitude(toGain(-12));
	osc.setUnisonVoices(7);
	osc.setUnisonDetune(0.5);
	osc.setUnisonBlend(0.7);

	Clock sequencerClock;
	sequencerClock.setBPM(bpm * subdivisions);

	Clock envelopeClock;
	envelopeClock.setPulseLength(0.3);
	envelopeClock.setBPM(bpm * subdivisions);

	Envelope envelope;
	envelope.setAttack(0);
	envelope.setRelease(1);
	envelope.setRelease(0.1);
	
	Sequencer sequencer;

	sequencer.getNotes() = {
		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_Eb4),
		intervalMultiplier(base, NOTE_G4),
		intervalMultiplier(base, NOTE_C4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_Eb4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_C4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_G4),
		intervalMultiplier(base, NOTE_Eb4),
	};
	sequencer.setCurrent(-1);

	sequencer.setClock(MODULE_OUT(&Clock::out, &sequencerClock));
	envelope.setGate(MODULE_OUT(&Clock::out, &envelopeClock));

	osc.setVCAmplitude(MODULE_OUT(&Envelope::out, &envelope));
	osc.setVCFrequency(MODULE_OUT(&Sequencer::out, &sequencer));

	master.setInput(MODULE_OUT(&Oscillator::out, &osc));

	master.play();
	
	//debugWriteToPCM("audio.pcm", (MODULE_OUT(&Oscillator::out, &osc)), format, 15);
	

	WAIT();

	return 0;
}

