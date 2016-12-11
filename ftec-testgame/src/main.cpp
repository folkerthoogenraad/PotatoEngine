#include "game/Razura.h"
#include "engine/DesktopEngine.h"
#include "logger/log.h"

int main(void)
{
	ftec::DesktopEngine::create<ftec::Razura>();

	return 0;
}

