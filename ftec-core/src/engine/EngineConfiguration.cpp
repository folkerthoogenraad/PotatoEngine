#include "EngineConfiguration.h"


#include "resources/ResourceManager.h"

#include "io/INIFile.h"
#include "logger/log.h"

namespace ftec {


	void EngineConfiguration::init(const std::string &filename)
	{
		auto file = INIFile::load(filename);

		if (!file) {
			LOG_WARNING("settings/config.ini does not exist.");
			//TODO generate the file with default values in this case
		}

		{
			INISegment *windowSegment = file->getSegmentByName("Window");

			if (!windowSegment) {
				LOG_WARNING(filename << " does not contain segment [Window].");
				return;
			}

			width = windowSegment->getInt("width", 1280); //TODO load default values rightly
			height = windowSegment->getInt("height", 720);
			fullscreen = windowSegment->getBool("fullscreen", false);
			vsync = windowSegment->getBool("vsync", false);
			msaa = windowSegment->getInt("msaa", 4);
			targetfps = windowSegment->getInt("targetfps", -1);
			framesleep = windowSegment->getFloat("framesleep", 0);
		}
	}

}
