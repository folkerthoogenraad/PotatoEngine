#include "AudioSystem.h"

#include "logger/log.h"

#include <assert.h>
#include <al.h>
#include <alc.h>

namespace ftec {


	//Auch?
	static ALCdevice *g_Device;
	static ALCcontext *g_Context;

	static void checkError() {
		ALCenum error;

		error = alGetError();
		if (error != AL_NO_ERROR)
			LOG("OpenAL error : " << error);
	}

	static void initAL() {
		static bool init = false;

		if (init)
			return;

		g_Device = alcOpenDevice(nullptr);

		if (!g_Device) {
			LOG("Failed to open default playback device. ");
		}

		checkError();

		g_Context = alcCreateContext(g_Device, NULL);

		if (!alcMakeContextCurrent(g_Context)) {
			LOG("Failed to create context and make context current.");
		}

		checkError();

		init = true;
	}

	AudioSystem::AudioSystem(AudioFormat format)
		:m_Format(format)
	{
		initAL();

		alListener3f(AL_POSITION, 0, 0, 0);
		alListener3f(AL_VELOCITY, 0, 0, 0);
	}
	AudioFormat::AudioFormat(size_t sampleRate, size_t bitsPerSample, AudioType type)
		: m_SampleRate(sampleRate), m_BitsPerSample(bitsPerSample), m_Type(type)
	{
		assert(bitsPerSample == 8 || bitsPerSample == 16, "Bits per sample must be either 8 or 16 bits.");
	}
}
