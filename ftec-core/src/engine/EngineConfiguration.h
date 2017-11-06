#pragma once

#include <string>

#define DEFAULT_GLOBAL_CONFIG_FILE "settings/config.ini"

namespace ftec {

	/**
	 * The EngineConfiguration, the startup parameters for the engine.
	*/
	struct EngineConfiguration {
		int width; /**< Width of the default window*/
		int height; /**< Height of the default window*/
		bool fullscreen; /**< Is the window fullscreen*/
		bool vsync; /**< Whether the window uses vertical synchronization*/
		int msaa; /**< The number of multisample anti aliasing buffers things (x1, x2, x4, x8, x16)*/
		int targetfps; /**< Target FPS, in case vsync is off but you still want a frame limiter*/

		/**
		 * The time, in milliseconds, the Engine sleeps BEFORE polling input and updating the game. 
		 * If your game update and render only takes 1 ms, putting this to about 14ms on a 60fps vsynced game will 
		 * reduce input lag
		 */
		float framesleep; 

	public:
		/**
		 * Reads the configuration from a configuration file. use DEFAULT_GLOBAL_CONFIG_FILE for the default file (settings/config.ini)
		*/
		void init(const std::string &filename);
	};
}