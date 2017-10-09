#pragma once

#include "potato_ui/Node.h"

namespace modularsynth{
	class OscillatorNode : public potato::Node {
	public:
		OscillatorNode();

		void init() override;
	};
}
