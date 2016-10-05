#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

int main(void)
{
	ftec::Engine::create<ftec::Razura>();
	return 0;
}

