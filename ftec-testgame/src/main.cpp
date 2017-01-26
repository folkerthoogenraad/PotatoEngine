#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "math/Rational.h"
#include "math/BSP3.h"

#include "math/Plane.h"
#include "math/collision.h"
#include "math/Ray3.h"

void test1()
{
	using namespace ftec;

	BSP3<int> bsp;

	Vector3r offset = Vector3r(0, 0, 1);

	Vector3r a = Vector3r(1, 5, 0);
	Vector3r b = Vector3r(2, 7, 0);
	Vector3r c = Vector3r(6, 9, 0);
	Vector3r d = Vector3r(9, 8, 0);
	Vector3r e = Vector3r(8, 2, 0);
	Vector3r f = Vector3r(4, 1, 0);

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

	Vector3r offset = Vector3r(0, 0, 1);

	Vector3r a = Vector3r(1, 4, 0);
	Vector3r b = Vector3r(2, 5, 0);
	Vector3r c = Vector3r(4, 5, 0);
	Vector3r d = Vector3r(5, 4, 0);
	Vector3r e = Vector3r(5, 2, 0);
	Vector3r f = Vector3r(4, 1, 0);
	Vector3r g = Vector3r(2, 1, 0);
	Vector3r h = Vector3r(1, 2, 0);

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

	Vector3r offset = Vector3r(0, 0, 1);

	Vector3r a = Vector3r(2, 2, 0);
	Vector3r b = Vector3r(4, 4, 0);
	Vector3r c = Vector3r(5, 1, 0);
	
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

void test4()
{
	using namespace ftec;

	BSP3<rational> bsp;

	Vector3r offset = Vector3r(0, 0, 1);

	Vector3r a = Vector3r(0, 2, 0);
	Vector3r b = Vector3r(2, 2, 0);
	Vector3r c = Vector3r(0, 0, 0);
	Vector3r d = Vector3r(2, 0, 0);

	Vector3r e = Vector3r(1, 3, 0);
	Vector3r f = Vector3r(3, 3, 0);
	Vector3r g = Vector3r(1, 1, 0);
	Vector3r h = Vector3r(3, 1, 0);

	Vector3r phantom = Vector3r(0, 3, 0);

	//Top and bottom
	bsp.insert(Triangle3r(
		c + offset, phantom + offset, f + offset
	));
	bsp.insert(Triangle3r(
		c, phantom, f
	));

	//Box a
	bsp.insert(Triangle3r(
		a, b, a + offset
	));
	bsp.insert(Triangle3r(
		b, d, b + offset
	));
	bsp.insert(Triangle3r(
		d, c, d + offset
	));
	bsp.insert(Triangle3r(
		c, a, c + offset
	));

	//Box b
	bsp.insert(Triangle3r(
		e, f, e + offset
	));
	bsp.insert(Triangle3r(
		f, h, f + offset
	));
	bsp.insert(Triangle3r(
		h, g, h + offset
	));
	bsp.insert(Triangle3r(
		g, e, g + offset
	));

	LOG(bsp.cellcount());
}

void test5()
{
	using namespace ftec;

	Plane<rational> a(Triangle3r(
		Vector3r(1, 1, 0),
		Vector3r(4, 3, 0),
		Vector3r(1, 1, 1)
	));
	Plane<rational> b(Triangle3r(
		Vector3r(2, 4, 0),
		Vector3r(4, 0, 0),
		Vector3r(2, 4, 1)
	));

	LOG(a);
	LOG(b);
	
	auto r = intersectRay(a, b).result;

	LOG(r.direction);
	LOG(r.origin);
}

int main(void)
{
	ftec::DesktopEngine::create<ftec::Razura>();

	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	
	WAIT();

	return 0;
}

