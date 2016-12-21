#include "EngineConfiguration.h"

#include "engine/Engine.h"

#include "resources/ResourceManager.h"

#include "io/INIFile.h"
#include "logger/log.h"

namespace ftec {

	int EngineConfiguration::width = 1280;
	int EngineConfiguration::height = 720;
	bool EngineConfiguration::fullscreen = false;
	bool EngineConfiguration::vsync = true;
	int EngineConfiguration::msaa = 4;
	int EngineConfiguration::targetfps = -1;

	void EngineConfiguration::init()
	{
		auto file = Engine::getResourceManager().load<INIFile>(DEFAULT_GLOBAL_CONFIG_FILE);

		if (!file) {
			LOG_WARNING("settings/config.ini does not exist.");
			//TODO generate the file with default values in this case
		}

		{
			INISegment *windowSegment = file->getSegmentByName("Window");

			if (!windowSegment) {
				LOG_WARNING("settings/config.ini does not contain segment [Window].");
				return;
			}

			width = windowSegment->getInt("width", 1280); //TODO load default values rightly
			height = windowSegment->getInt("height", 720);
			fullscreen = windowSegment->getBool("fullscreen", false);
			vsync = windowSegment->getBool("vsync", false);
			msaa = windowSegment->getInt("msaa", 4);
			targetfps = windowSegment->getInt("targetfps", -1);
		}
	}

}
