#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "math/Rational.h"
#include "math/Line2.h"

#include "math/collision.h"

int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();
	
	Vector2<Rationali> a(-1, 3);
	Vector2<Rationali> b(4, 1);
	Vector2<Rationali> c(0, -2);
	Vector2<Rationali> d(3, 0);

	Line2<Rationali> linea(a, b);
	Line2<Rationali> lineb(c, d);

	LOG(linea.a << " " << linea.b);
	LOG(lineb.a << " " << lineb.b);

	auto res = intersect(linea, lineb).result;

	LOG(res);

	WAIT();

	return 0;
}

