#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "collision/CollisionWorld.h"
#include "collision/CollisionTransform.h"

int main(void)
{
	ftec::DesktopEngine::create<ftec::Razura>();

	WAIT();
	return 0;
}

