#pragma once

#include "potato_ui/Node.h"

namespace modularsynth{
	class OscillatorNode : public potato::Node {
	public:
		OscillatorNode(std::shared_ptr<ftec::EngineContext> context);

		void init() override;
	};
}
