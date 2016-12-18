#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include <memory>
#include <algorithm>
#include "math/Vector3.h"

#include "io/INIFile.h"


int main(void)
{
	using namespace ftec;

	ftec::DesktopEngine::create<ftec::Razura>();

	WAIT();
	return 0;
}

