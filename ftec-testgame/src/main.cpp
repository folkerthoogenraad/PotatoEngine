#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "math/Rational.h"
#include "math/BSP3.h"

void test1()
{
	using namespace ftec;

	BSP3<int> bsp;

	Vector3i offset = Vector3i(0, 0, 1);

	Vector3i a = Vector3i(1, 5, 0);
	Vector3i b = Vector3i(2, 7, 0);
	Vector3i c = Vector3i(6, 9, 0);
	Vector3i d = Vector3i(9, 8, 0);
	Vector3i e = Vector3i(8, 2, 0);
	Vector3i f = Vector3i(4, 1, 0);

	bsp.insert(Triangle3i(
		a, d, a + offset
	));

	bsp.insert(Triangle3i(
		b, e, b + offset
	));

	bsp.insert(Triangle3i(
		c, f, c + offset
	));

	LOG(bsp.cellcount());
}

void test2()
{
	using namespace ftec;

	BSP3<int> bsp;

	Vector3i offset = Vector3i(0, 0, 1);

	Vector3i a = Vector3i(1, 4, 0);
	Vector3i b = Vector3i(2, 5, 0);
	Vector3i c = Vector3i(4, 5, 0);
	Vector3i d = Vector3i(5, 4, 0);
	Vector3i e = Vector3i(5, 2, 0);
	Vector3i f = Vector3i(4, 1, 0);
	Vector3i g = Vector3i(2, 1, 0);
	Vector3i h = Vector3i(1, 2, 0);

	bsp.insert(Triangle3i(
		a, d, a + offset
	));

	bsp.insert(Triangle3i(
		c, f, c + offset
	));

	bsp.insert(Triangle3i(
		e, h, e + offset
	));

	bsp.insert(Triangle3i(
		g, b, g + offset
	));


	LOG(bsp.cellcount());
}

void test3()
{
	using namespace ftec;

	BSP3<int> bsp;

	Vector3i offset = Vector3i(0, 0, 1);

	Vector3i a = Vector3i(2, 2, 0);
	Vector3i b = Vector3i(4, 4, 0);
	Vector3i c = Vector3i(5, 1, 0);
	
	bsp.insert(Triangle3i(
		a, b, a + offset
	));

	bsp.insert(Triangle3i(
		b, c, b + offset
	));

	bsp.insert(Triangle3i(
		c, a, c + offset
	));

	LOG(bsp.cellcount());
}

int main(void)
{

	//ftec::DesktopEngine::create<ftec::Razura>();

	test1();
	test2();
	test3();
	
	WAIT();

	return 0;
}

