#pragma once

#include "EngineContext.h"

namespace ftec {
	
	class Game;

	class DesktopEngine {
		struct engine_resource;
	public:
		static void init();
		static void loop(Game &game, std::shared_ptr<EngineContext> context);
		static void destroy();

		static std::shared_ptr<EngineContext> createEngineContext();

		template<typename T>
		static void create()
		{
			//Use the nice resource safety here
			//engine_resource engine;

			{
				//TODO resource safety here :')
				auto context = createEngineContext();

				T game;
				game.init(context);

				loop(game, context);

				game.destroy();
			}

		}

	private:
		struct engine_resource {
			engine_resource() { init(); }
			~engine_resource() { destroy(); }
		};
	};

}