#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include "networking/Client.h"

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	test_client();

	WAIT();

	return 0;
}

