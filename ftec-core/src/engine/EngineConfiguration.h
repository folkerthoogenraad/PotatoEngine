#pragma once

namespace ftec {
	struct EngineConfiguration {
		static int width;
		static int height;
		static bool fullscreen;
		static bool vsync;
		static int msaa;
		static int targetfps;
		static float framesleep;

		static void init();
	
	public:
		EngineConfiguration() = delete;
		~EngineConfiguration() = delete;
	};
}