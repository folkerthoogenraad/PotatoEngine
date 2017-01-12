#pragma once

#include <memory>

#include "engine/Game.h"

namespace potato {
	class PotatoUI;
}

namespace ftec {
	class Razura : public Game{
		std::shared_ptr<potato::PotatoUI> m_UI;
	public:
		Razura() = default;
		virtual ~Razura() = default;

		void update() override;
		void render() override;
		void init() override;
		void destroy() override;
	};
}