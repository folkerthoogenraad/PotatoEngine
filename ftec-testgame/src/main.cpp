#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "collision/CollisionWorld.h"
#include "collision/CollisionTransform.h"

void test()
{
	using namespace ftec;
	
	CollisionWorld world;

	CollisionTransform a(Rectanglef::centered(0, 0, 1, 1), &world);
	CollisionTransform b(Rectanglef::centered(0, 0, 1, 1), &world);
	CollisionTransform c(Rectanglef::centered(0, 0, 1, 1), &world);
	

}

int main(void)
{
	//ftec::DesktopEngine::create<ftec::Razura>();
	test();

	WAIT();
	return 0;
}

