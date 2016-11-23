#pragma once
#include <iostream>

#define LOG(message) std::cout << message << std::endl
#define LOG_ERROR(message) std::cerr << "(" << __FILE__ << ":" << __LINE__ << ")" << message << std::endl

#define LOG_DEBUG(message) std::cout << "(" << __FILE__ << ":" << __LINE__ << ")" << message << std::endl

#define TERMINATE(message) std::cerr << "SYSTEM ERROR:" << std::endl << message << std::endl << "Press any key to continue..."; std::cin.get(); exit(-1)
#define WAIT() std::cout << "Press any key to continue... "; std::cin.get()