#include "game/Razura.h"
#include "engine/Engine.h"

#include "logger/log.h"

#include "math/plane.h"


int main(void)
{
	using namespace ftec;

	ftec::Engine::create<ftec::Razura>();

	WAIT();

	return 0;
}

