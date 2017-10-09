#pragma once

namespace ftec {

	struct AudioFormat {
	public:
		enum AudioType {
			Mono,
			Stereo
		};
	private:
		size_t m_SampleRate;
		size_t m_BitsPerSample;
		AudioType m_Type;
	public:
		AudioFormat(size_t sampleRate, size_t bitsPerSample, AudioType type);

		size_t getSampleRate() const { return m_SampleRate; }
		size_t getBitsPerSample() const { return m_BitsPerSample; }

		AudioType getType() const { return m_Type; }
	};

	class AudioSystem {
	private:
		AudioFormat m_Format;
	public:
		AudioSystem(AudioFormat format);

		inline AudioFormat getFormat() const { return m_Format; }
	};

}