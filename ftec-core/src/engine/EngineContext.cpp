#include "EngineContext.h"

#include <assert.h>

namespace ftec {
	EngineContext::EngineContext(EngineConfiguration configuration, std::unique_ptr<Window> window, std::unique_ptr<ResourceManager> resources)
		: m_Config(configuration), m_Window(std::move(window)), m_Resources(std::move(resources))
	{
		assert(m_Window != nullptr);
		assert(m_Resources != nullptr);
	}


	const EngineConfiguration & EngineContext::getConfiguration() const
	{
		return m_Config;
	}
}
