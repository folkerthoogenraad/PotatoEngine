#include "logger/log.h"
#include <memory>
#include "engine/Engine.h"
#include "game/Razura.h"
#include <iostream>
#include "potato_ui/Panel.h"
#include "io/defer.h"

int main(void)
{
	ftec::Engine::create(std::make_unique<ftec::Razura>());

	return 0;
}

