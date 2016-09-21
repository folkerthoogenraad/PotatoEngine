#include "logger/log.h"
#include <memory>
#include "engine/Engine.h"
#include "game/Razura.h"

#include <iostream>

int main(void)
{
	ftec::Engine::create(std::make_unique<ftec::Razura>());
	return 0;
}

