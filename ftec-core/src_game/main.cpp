#include "logger/log.h"
#include <memory>
#include "engine/Engine.h"
#include "game/Razura.h"

#include <iostream>
#include "math/rect.h"

int main(void)
{
	using namespace ftec;

	rect2i rect;
	rect.x() = 1;
	rect.y() = 2;
	rect.width() = 3;
	rect.height() = 4;


	TERMINATE("asdf");
	ftec::Engine::create(std::make_unique<ftec::Razura>());
	return 0;
}

