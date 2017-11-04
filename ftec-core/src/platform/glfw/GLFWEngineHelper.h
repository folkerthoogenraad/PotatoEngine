#pragma once

#include "engine/EngineContext.h"

namespace ftec {
	
	class Game;

	class GLFWEngineHelper {
	private:
		static void loop(Game &game, std::shared_ptr<EngineContext> context);
	public:
		static std::shared_ptr<EngineContext> createEngineContext();

		static void init();
		static void destroy();


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

	};

}