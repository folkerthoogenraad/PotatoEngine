#include "logger/log.h"
#include <memory>
#include "engine/Engine.h"
#include "game/Razura.h"
#include <iostream>
#include "potato_ui/Panel.h"
#include "io/defer.h"
#include "math/vec4.h"

int main(void)
{
	ftec::Engine::create<ftec::Razura>();
	WAIT();
	return 0;
}

