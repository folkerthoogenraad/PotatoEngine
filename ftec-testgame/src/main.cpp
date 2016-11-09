#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"
#include "io/XMLReader.h"

#include "math/collision.h"

int main(void)
{
	ftec::Engine::create<ftec::Razura>();

	WAIT();
	return 0;
}

