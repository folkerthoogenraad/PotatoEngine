#pragma once

#include "engine/Game.h"
#include "graphics/SpriteBatch.h"
#include "graphics/Sprite.h"

namespace ftec {
	class Razura : public Game{
	private:
		SpriteBatch batch;
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