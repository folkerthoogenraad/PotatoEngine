#include "ModularSystem.h"

#include "logger/log.h"

#include <thread>

namespace ftec {
	ModularSystem::ModularSystem(std::weak_ptr<AudioSystem> as)
		: m_System(as)
	{
		auto system = m_System.lock();

		if (!system) {
			LOG("No System attached.");
			return;
		}

		for (int i = 0; i < m_Datas.size(); i++) {
			m_Buffers[i] = std::make_unique<AudioBuffer>(system);
			m_Datas[i].resize(MODULAR_BUFFER_SIZE);

			std::fill(m_Datas[i].begin(), m_Datas[i].end(), 0);
			m_Buffers[i]->setDataNormalized(m_Datas[i], system->getFormat());
		}

		m_Source = std::make_unique<AudioSource>(system);
	}

	void ModularSystem::setInput(AudioModuleOutput output)
	{
		m_Output = output;
	}

	void ModularSystem::play()
	{
		auto system = m_System.lock();

		if (!system) {
			LOG("No System attached.");
			return;
		}

		for (int i = 0; i < m_Buffers.size(); i++)
			m_Source->queueBuffer(*m_Buffers[i]);
		
		m_Source->play();

		int currentPlay = 0;
		int currentFill = 0;

		while (true) {
			if (m_Source->getBuffersProcessed() > 0) {

				currentPlay = (currentPlay + 1) % m_Buffers.size();
				currentFill = (currentPlay - 1) % m_Buffers.size();
				
				// Unqueue the fillbuffer
				m_Source->unqueueBuffer(*m_Buffers[currentFill]);

				if (m_Output) {
					m_Output(m_Datas[currentFill], system->getFormat());
				}else {
					std::fill(m_Datas[currentFill].begin(), m_Datas[currentFill].end(), 0);
				}

				//for (int i = 0; i < m_Datas[currentFill].size(); i++)
				//	LOG(m_Datas[currentFill][i]);

				m_Buffers[currentFill]->setDataNormalized(m_Datas[currentFill], system->getFormat());

				// Queue the newly filled
				m_Source->queueBuffer(*m_Buffers[currentFill]);
			}
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
}
