#pragma once

#include "engine/Game.h"

namespace ftec {
	class Razura : public Game{

	public:
		Razura() = default;
		virtual ~Razura() = default;

		void update() override;
		void render() override;
		void init() override;
		void destroy() override;
	};
}