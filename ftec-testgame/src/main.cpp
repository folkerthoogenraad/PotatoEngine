#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include "util/hash.h"
#include <functional>

int main(void)
{
	using namespace ftec;

	ftec::DesktopEngine::create<ftec::Razura>();

	WAIT();

	return 0;
}

