#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include "potato_ui/Event.h"

#include "graphics/ImageHelper.h"

#include "util/not_null.h"
#include "graphics/SoftwareGraphics.h"


int main(void)
{
	using namespace ftec;

	ftec::DesktopEngine::create<ftec::Razura>();
	
	//test();

	WAIT();

	return 0;
}

