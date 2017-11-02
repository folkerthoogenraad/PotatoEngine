#pragma once

#include <string>

#define DEFAULT_GLOBAL_CONFIG_FILE "settings/config.ini"

namespace ftec {
	struct EngineConfiguration {
		int width;
		int height;
		bool fullscreen;
		bool vsync;
		int msaa;
		int targetfps;
		float framesleep;

	public:
		void init(const std::string &filename);
	};
}