#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"
#include "io/XMLReader.h"

int main(void)
{
	ftec::Engine::create<ftec::Razura>();
	return 0;
}

