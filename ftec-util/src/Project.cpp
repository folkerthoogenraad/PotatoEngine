#include "Project.h"

#include <filesystem>

namespace project {

	static void createDirectory(const std::string &dir)
	{
		using namespace std::experimental;
		if (!filesystem::exists(dir)) {
			filesystem::create_directory(dir);
		}
	}

	void project::init()
	{
		createDirectory("fonts");
		createDirectory("mesh");
		createDirectory("settings");
		createDirectory("shaders");
		createDirectory("textures");
		createDirectory("src");
	}
}
