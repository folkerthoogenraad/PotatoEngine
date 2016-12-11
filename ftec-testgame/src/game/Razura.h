#pragma once

#include "engine/Game.h"
#include "graphics/Graphics2D.h"
#include "graphics/Sprite.h"
#include "potato_ui/PotatoUI.h"

namespace ftec {
	class Razura : public Game{
	private:
		Graphics2D graphics;
	public:
		Razura() = default;
		virtual ~Razura() = default;

		void update() override;
		void render() override;
		void init() override;
		void destroy() override;
	};
}