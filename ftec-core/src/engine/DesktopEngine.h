#pragma once

namespace ftec {
	
	class Game;

	class DesktopEngine {
		struct engine_resource;
	public:
		static void init();
		static void loop(Game &game);
		static void destroy();

		template<typename T>
		static void create()
		{
			//Use the nice resource safety here
			engine_resource engine;

			{
				//TODO resource safety here :')

				T game;
				game.init();

				loop(game);

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