#include "game/Razura.h"

#include "platform/glfw/GLFWEngineHelper.h"

#include "logger/log.h"
#include <functional>


#include "graphics/Image.h"
#include "graphics/SoftwareGraphics.h"
#include "graphics/ImageHelper.h"

#include "graphics/GL.h"

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

void doAudio() 
{
	using namespace ftec;

	AudioFormat format(
		44100,
		16,
		AudioFormat::Mono
	);

	//test();

	auto system = std::make_shared<AudioSystem>(format);

	ModularSystem master(system);

	const double base = 220;
	const double bpm = 140;
	const double subdivisions = 1;

	Oscillator osc;
	osc.setFrequency(base);
	osc.setWaveType(Oscillator::Noise);
	osc.setAmplitude(toGain(0));
	osc.setUnisonVoices(1);
	osc.setUnisonDetune(0.5);
	osc.setUnisonBlend(0.7);

	Oscillator modulator;
	modulator.setFrequency(3);
	modulator.setWaveType(Oscillator::Sine);
	modulator.setRange(0.99, 1.01);

	Clock sequencerClock;
	sequencerClock.setBPM(bpm * subdivisions);

	Clock envelopeClock;
	envelopeClock.setBPM(bpm * subdivisions);
	envelopeClock.setPulseLength(0.01); // 0.005

	Envelope envelope;
	envelope.setAttack(0);
	envelope.setSustain(1);
	envelope.setRelease(1);
	envelope.setRelease(0);

	Sequencer sequencer;

	sequencer.getNotes() = {
		// C Major
		intervalMultiplier(base, NOTE_C4),
		intervalMultiplier(base, NOTE_C4),

	};
	sequencer.setRandomness(0);
	sequencer.setRandomRange(0.5, 2.0);

	sequencer.setCurrent(-1);
	sequencer.setLegatoTime(0);

	SimpleMath math;
	math.addAudioInput(MODULE_OUT(&Sequencer::out, &sequencer));
	//math.addAudioInput(MODULE_OUT(&Oscillator::out, &modulator));

	Delay delay;
	delay.setFilterCutoff(8000);
	delay.setUseFilter(true);
	delay.setDelayFrequency(NOTE_A4 / 4);
	delay.setFeedback(0.99);
	delay.setInput(MODULE_OUT(&Oscillator::out, &osc));

	sequencer.setClock(MODULE_OUT(&Clock::out, &sequencerClock));
	envelope.setGate(MODULE_OUT(&Clock::out, &envelopeClock));

	osc.setVCAmplitude(MODULE_OUT(&Envelope::out, &envelope));
	osc.setVCFrequency(MODULE_OUT(&SimpleMath::out, &math));

	master.setInput(MODULE_OUT(&Delay::out, &delay));
	//master.setInput(MODULE_OUT(&Filter::out, filter));

	master.play();

	//debugWriteToPCM("audio.pcm", (MODULE_OUT(&Delay::out, &delay)), format, toBarSeconds(bpm, 4) * 16);

	WAIT();
}

void createEngineAndShitBricks()
{
	using namespace ftec;

	GLFWEngineHelper::init();

	std::array<std::thread, 1> threads;

	for (int i = 0; i < threads.size(); i++) {
		threads[i] = std::thread([]() {
			GLFWEngineHelper::create<ftec::Razura>();
		});
	}

	for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
	}

	GLFWEngineHelper::destroy();
}

int main(void)
{
	using namespace ftec;

	const int windowWidth = 8;
	const int windowHeight = 4;

	const int windowHSpacing = 4;
	const int windowVSpacing = 4;

	Image image(256, 256);
	SoftwareGraphics graphics = SoftwareGraphics(&image);


	Paint paint;
	paint.mode = Paint::FILL;
	paint.color = Color32::black();

	graphics.drawRectangle(paint, 0, 0, image.getWidth(), image.getHeight());
	
	paint.color = Color32::white();

	int currentX = windowHSpacing;
	int currentY = windowVSpacing;

	while (currentY < image.getHeight()){

		uint8_t v = (uint8_t) (random() * 256);

		paint.color = Color32(v,v,v,255);
		
		//TODO draw the window at currentX and currentY
		graphics.drawRectangle(paint, currentX, currentY, windowWidth, windowHeight);

		currentX += windowWidth + windowHSpacing;

		if (currentX > image.getWidth()) {
			currentY += windowHeight + windowVSpacing;
			currentX = windowHSpacing;
		}
	}

	image.flip();
	saveImage(image, "windows.png");

	WAIT();

	return 0;
}

