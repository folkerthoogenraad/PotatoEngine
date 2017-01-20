#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "math/BSP2.h"

void testCase1()
{
	using namespace ftec;

	BSP2i bsp;

	bsp.build({
		Line2i(Vector2i(0,4), Vector2i(0,-4)),
		Line2i(Vector2i(-3,0), Vector2i(4,0))
	});

	LOG("Test case 1 : " << bsp.cellcount());
}

void testCase2()
{
	using namespace ftec;

	BSP2i bsp;

	bsp.build({
		Line2i(Vector2i(1,3), Vector2i(-1,-3)),
		Line2i(Vector2i(2, -1), Vector2i(-2,1)),
		Line2i(Vector2i(2,2), Vector2i(3,1))
	});

	LOG("Test case 2 : " << bsp.cellcount());
}

void testCase3()
{
	using namespace ftec;

	BSP2i bsp;

	bsp.build({
		Line2i(Vector2i(0,3), Vector2i(0,-3)),
		Line2i(Vector2i(2,2), Vector2i(4,0)),
		Line2i(Vector2i(-2,0), Vector2i(-3,-2)),
		Line2i(Vector2i(-1,-1), Vector2i(1, -2)),

		Line2i(Vector2i(0,2), Vector2i(0,-2)),
	});

	LOG("Test case 3 : " << bsp.cellcount());
}

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	testCase1();
	testCase2();
	testCase3();

	WAIT();

	return 0;
}

