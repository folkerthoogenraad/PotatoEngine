#pragma once

#include "engine/Game.h"
#include "graphics/Graphics2D.h"
#include "graphics/Sprite.h"
#include "potato_ui/Panel.h"

namespace ftec {
	class Razura : public Game{
	private:
		Graphics2D graphics;
		potato::Panel panel;
		Sprite sprite;
	public:
		Razura();
		virtual ~Razura() = default;

		void update() override;
		void render() override;
		void init() override;
		void destroy() override;
	};
}