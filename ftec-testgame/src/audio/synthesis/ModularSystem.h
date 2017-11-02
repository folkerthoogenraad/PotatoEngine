#pragma once

#include <memory>
#include <array>

#include "audio/AudioSystem.h"
#include "audio/AudioSource.h"
#include "audio/AudioBuffer.h"
#include "AudioModule.h"

#define MODULAR_BUFFER_SIZE 256
#define MODULAR_BUFFER_COUNT 16

namespace ftec {

	class ModularSystem {
		AudioModuleOutput m_Output;

		std::weak_ptr<AudioSystem> m_System;

		std::array<std::vector<double>, MODULAR_BUFFER_COUNT> m_Datas;
		std::array<std::unique_ptr<AudioBuffer>, MODULAR_BUFFER_COUNT> m_Buffers;

		std::unique_ptr<AudioSource> m_Source;
	public:
		ModularSystem(std::weak_ptr<AudioSystem> system);

		void setInput(AudioModuleOutput output);

		void play();
	};

}