#include "AudioSource.h"

#include <al.h>

namespace ftec {

	AudioSource::AudioSource(std::weak_ptr<AudioSystem> system)
		: m_System(system)
	{
		alGenSources(1, &m_SourceID);
		alSourcef(m_SourceID, AL_GAIN, 1);
		alSourcef(m_SourceID, AL_PITCH, 1);
		alSource3f(m_SourceID, AL_POSITION, 0, 0, 0);
	}

	void AudioSource::play()
	{
		alSourcePlay(m_SourceID);
	}

	void AudioSource::play(AudioBuffer & clip)
	{
		alSourcei(m_SourceID, AL_BUFFER, clip.getBuffer());
		play();
	}

	void AudioSource::queueBuffer(AudioBuffer & buffer)
	{
		unsigned int b = buffer.getBuffer();
		alSourceQueueBuffers(m_SourceID, 1, &b);
	}

	void AudioSource::unqueueBuffer(AudioBuffer & buffer)
	{
		unsigned int b = buffer.getBuffer();
		alSourceUnqueueBuffers(m_SourceID, 1, &b);
	}

	int AudioSource::getBuffersProcessed()
	{
		int v;
		alGetSourcei(m_SourceID, AL_BUFFERS_PROCESSED, &v);
		return v;
	}

	AudioSource::~AudioSource()
	{
		alDeleteSources(1, &m_SourceID);
	}
}
