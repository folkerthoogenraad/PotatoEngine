#pragma once

#include <memory>
#include <array>

#include "audio/AudioSystem.h"
#include "audio/AudioSource.h"
#include "audio/AudioBuffer.h"
#include "AudioModule.h"

#define MODULAR_BUFFER_SIZE 8196

namespace ftec {

	class ModularSystem {
		AudioModuleOutput m_Output;

		std::weak_ptr<AudioSystem> m_System;

		std::array<std::vector<double>, 2> m_Datas;
		std::array<std::unique_ptr<AudioBuffer>, 2> m_Buffers;

		std::unique_ptr<AudioSource> m_Source;
	public:
		ModularSystem(std::weak_ptr<AudioSystem> system);

		void setInput(AudioModuleOutput output);

		void play();
	};

}