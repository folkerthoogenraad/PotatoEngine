#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "collision/CollisionWorld.h"
#include "collision/CollisionTransform.h"

#include <memory>
#include <algorithm>
#include "math/Vector3.h"

void test()
{
	using namespace ftec;
	
	CollisionWorld world;

	CollisionTransform transform1(Rectanglef::centered(0, 0, 1, 1), &world);
	CollisionTransform transform2(Rectanglef::centered(0, 0, 1, 1), &world);
	CollisionTransform transform3(Rectanglef::centered(0, 0, 1, 1), &world);
}

int main(void)
{
	ftec::DesktopEngine::create<ftec::Razura>();

	WAIT();
	return 0;
}

