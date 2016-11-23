#include "game/Razura.h"
#include "engine/Engine.h"

#include "logger/log.h"

int main(void)
{
	ftec::Engine::create<ftec::Razura>();

	WAIT();
	return 0;
}

