
#include <vector>
#include <string>
#include <iostream>

#include "Project.h"

std::vector<std::string> commandlineArguments;

void help()
{
	std::cout << "Unknown function " << commandlineArguments[1];
	std::cout << "Available functions are: ";
	std::cout << "init - Creates a new project in the current directory";
}

void init()
{
	project::init();
}

int program()
{
	if (commandlineArguments.size() < 2) {
		help();
	}

	else if (commandlineArguments[1] == "init") {
		init();
	}

	else {
		help();
	}
	std::cin.get();

	return 0;
}

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		commandlineArguments.push_back(argv[i]);
	
	return program();
}