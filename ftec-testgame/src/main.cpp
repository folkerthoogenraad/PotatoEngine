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
#include "audio\synthesis\Filter.h"
#include "audio\synthesis\Clock.h"
#include "audio\synthesis\Envelope.h"
#include "audio\synthesis\Distortion.h"
#include "audio\synthesis\Sequencer.h"
#include "audio\synthesis\SimpleMath.h"
#include "audio\synthesis\Delay.h"

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

	const double base = 220;
	const double bpm = 128;
	const double subdivisions = 4;

	Oscillator osc;
	osc.setFrequency(base * 0.5);
	osc.setWaveType(Oscillator::Sawtooth);
	osc.setAmplitude(toGain(0));
	osc.setUnisonVoices(7);
	osc.setUnisonDetune(0.5);
	osc.setUnisonBlend(0.7);

	Oscillator modulator;
	modulator.setFrequency(5);
	modulator.setWaveType(Oscillator::Sine);
	modulator.setRange(0.98, 1.02);

	Clock sequencerClock;
	sequencerClock.setBPM(bpm * subdivisions);

	Clock envelopeClock;
	envelopeClock.setPulseLength(1);
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
	sequencer.setLegatoTime(0.1);

	SimpleMath math;
	math.addAudioInput(MODULE_OUT(&Sequencer::out, &sequencer));
	math.addAudioInput(MODULE_OUT(&Oscillator::out, &modulator));

	Filter filter;
	filter.setCutoffFrequency(220);
	filter.setInput(MODULE_OUT(&Oscillator::out, &osc));

	sequencer.setClock(MODULE_OUT(&Clock::out, &sequencerClock));
	envelope.setGate(MODULE_OUT(&Clock::out, &envelopeClock));

	osc.setVCAmplitude(MODULE_OUT(&Envelope::out, &envelope));
	osc.setVCFrequency(MODULE_OUT(&SimpleMath::out, &math));

	std::vector<double> data;
	data.resize(MODULAR_BUFFER_SIZE);

	int times = 10000;

	LOG("Starting...");
	auto time = std::chrono::system_clock::now();
	
	for(int i = 0; i < times; i++)
		filter.out(data, format);

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

	srand(static_cast <unsigned> (time(0)));

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
	osc.setFrequency(base);
	osc.setWaveType(Oscillator::HalfSine);
	osc.setAmplitude(toGain(-6));
	osc.setUnisonVoices(1);
	osc.setUnisonDetune(0.5);
	osc.setUnisonBlend(0.7);


	Oscillator modulator;
	modulator.setFrequency(3);
	modulator.setWaveType(Oscillator::Sine);
	modulator.setRange(0.99,1.01);
	
	Clock sequencerClock;
	sequencerClock.setBPM(bpm * subdivisions);

	Clock envelopeClock;
	envelopeClock.setBPM(bpm * subdivisions);
	envelopeClock.setPulseLength(0.1);

	Envelope envelope;
	envelope.setAttack(0.02);
	envelope.setSustain(toGain(-16));
	envelope.setDecay(0.1);
	envelope.setRelease(1);
	envelope.setRelease(0.1);
	
	Sequencer sequencer;

	sequencer.getNotes() = { 
		// C Major
		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_E4),
		intervalMultiplier(base, NOTE_G4),

		intervalMultiplier(base, NOTE_E4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_C4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_G4),

		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_E4),
		intervalMultiplier(base, NOTE_G4),

		intervalMultiplier(base, NOTE_E4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_C4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_G4),

		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_E4),
		intervalMultiplier(base, NOTE_G4),
		intervalMultiplier(base, NOTE_E4),

		//B major
		intervalMultiplier(base, NOTE_B4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_D4),
		intervalMultiplier(base, NOTE_Gb4),

		intervalMultiplier(base, NOTE_D4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_B4),
		intervalMultiplier(base, NOTE_Gb4),

		intervalMultiplier(base, NOTE_B4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_D4),
		intervalMultiplier(base, NOTE_Gb4),

		intervalMultiplier(base, NOTE_D4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_B4),
		intervalMultiplier(base, NOTE_Gb4),

		intervalMultiplier(base, NOTE_B4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_D4),
		intervalMultiplier(base, NOTE_Gb4),
		intervalMultiplier(base, NOTE_D4),

		//A minor
		intervalMultiplier(base, NOTE_A4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_E4),

		intervalMultiplier(base, NOTE_C4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_A4),
		intervalMultiplier(base, NOTE_E4),

		intervalMultiplier(base, NOTE_A4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_E4),

		intervalMultiplier(base, NOTE_C4 * OCTAVE_UP),
		intervalMultiplier(base, NOTE_A4),
		intervalMultiplier(base, NOTE_E4),

		intervalMultiplier(base, NOTE_A4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_E4),
		intervalMultiplier(base, NOTE_C4),

		//G Major
		intervalMultiplier(base, NOTE_G4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_B4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_D4),

		intervalMultiplier(base, NOTE_B4),
		intervalMultiplier(base, NOTE_G4),
		intervalMultiplier(base, NOTE_D4),

		intervalMultiplier(base, NOTE_G4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_B4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_D4),

		intervalMultiplier(base, NOTE_B4),
		intervalMultiplier(base, NOTE_G4),
		intervalMultiplier(base, NOTE_D4),

		intervalMultiplier(base, NOTE_G4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_B4 * OCTAVE_DOWN),
		intervalMultiplier(base, NOTE_D4),
		intervalMultiplier(base, NOTE_B4 * OCTAVE_DOWN),

	};

	sequencer.setRandomness(0);
	sequencer.setRandomRange(0.5, 2.0);

	sequencer.setCurrent(-1);
	sequencer.setLegatoTime(0);

	SimpleMath math;
	math.addAudioInput(MODULE_OUT(&Sequencer::out, &sequencer));
	math.addAudioInput(MODULE_OUT(&Oscillator::out, &modulator));

	Filter filter;
	filter.setType(IIRFilter::LowPass);
	filter.setCutoffFrequency(20000);
	filter.setInput(MODULE_OUT(&Oscillator::out, &osc));

	Delay delay;
	delay.setDelayTime(0.2);
	delay.setFeedback(0.2);
	delay.setInput(MODULE_OUT(&Filter::out, &filter));

	sequencer.setClock(MODULE_OUT(&Clock::out, &sequencerClock));
	envelope.setGate(MODULE_OUT(&Clock::out, &envelopeClock));

	osc.setVCAmplitude(MODULE_OUT(&Envelope::out, &envelope));
	osc.setVCFrequency(MODULE_OUT(&SimpleMath::out, &math));

	master.setInput(MODULE_OUT(&Delay::out, &delay));

	master.play();
	
	//debugWriteToPCM("audio.pcm", (MODULE_OUT(&Delay::out, &delay)), format, toBarSeconds(bpm, 4) * 5);

	WAIT();

	return 0;
}

