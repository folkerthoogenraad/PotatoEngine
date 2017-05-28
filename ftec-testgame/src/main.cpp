#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"
#include "networking/Client.h"

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	Client client;
	client.connect("localhost", "9898");

	WAIT();

	return 0;
}

