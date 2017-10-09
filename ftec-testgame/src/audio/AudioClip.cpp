#include "AudioClip.h"

#include <al.h>
#include <assert.h>
#include <climits>

#include "logger/log.h"
#include "math/math.h"

namespace ftec {

	static ALenum getALFormat(AudioFormat format) 
	{
		if (format.getBitsPerSample() == 8 && format.getType() == AudioFormat::Mono)
			return AL_FORMAT_MONO8;
		if (format.getBitsPerSample() == 16 && format.getType() == AudioFormat::Mono)
			return AL_FORMAT_MONO16;
		if (format.getBitsPerSample() == 8 && format.getType() == AudioFormat::Stereo)
			return AL_FORMAT_STEREO8;
		if (format.getBitsPerSample() == 16 && format.getType() == AudioFormat::Stereo)
			return AL_FORMAT_STEREO16;

		assert(false);

		return AL_FORMAT_MONO8;
	}

	AudioBuffer::AudioBuffer(std::weak_ptr<AudioSystem> system)
		:m_System(system)
	{
		alGenBuffers(1, &m_Buffer);
	}

	AudioBuffer::~AudioBuffer()
	{
		alDeleteBuffers(1, &m_Buffer);
	}


	void AudioBuffer::setDataNormalized(std::vector<double>& data, AudioFormat format)
	{
		if (format.getBitsPerSample() == 8) {
			std::vector<unsigned char> values;
			values.resize(data.size());

			//TODO check this
			for (size_t i = 0; i < data.size(); i++) {
				values[i] = (unsigned char)clamp((double)0, (double)UCHAR_MAX, (data[i]) * (double)CHAR_MAX + CHAR_MAX + 1);
			}

			setData(values, format);
		}
		else {
			std::vector<short> values;
			values.resize(data.size());

			//TODO check this
			for (size_t i = 0; i < data.size(); i++) {
				values[i] = (short) clamp((double)SHRT_MIN, (double)SHRT_MAX, (data[i]) * (double)SHRT_MAX);
			}

			setData(values, format);
		}
	}

	void AudioBuffer::setDataRaw(void * data, size_t size, AudioFormat format)
	{
		alBufferData(m_Buffer, getALFormat(format), data, size, format.getSampleRate());
	}
}
