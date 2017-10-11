#pragma once

#include <memory>
#include <vector>

#include "AudioSystem.h"

namespace ftec {

	class AudioBuffer {
	private:
		unsigned int m_Buffer; 
		std::weak_ptr<AudioSystem> m_System;
	public:
		AudioBuffer(std::weak_ptr<AudioSystem> system);
		~AudioBuffer();

		template<typename T>
		void setData(std::vector<T> &data, AudioFormat format)
		{
			setDataRaw(&data[0], data.size() * sizeof(T), format);
		}

		void setDataNormalized(std::vector<double> &data, AudioFormat format);

		// If we go full const correct, this should not be const
		unsigned int getBuffer() { return m_Buffer; }
	private:
		void setDataRaw(void *data, size_t size, AudioFormat format);
	};

}