#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include <memory>
#include <algorithm>
#include <vector>

#include "math/precision.h"
#include "math/math.h"

#include "math/Line2.h"
#include "math/Triangle2.h"
#include "math/Circle.h"

#include <climits>

int main(void)
{
	using namespace ftec;
	/*
	Triangle2ll triangle(
		Vector2ll(INT_MIN + 1, INT_MIN + 1),
		Vector2ll(INT_MAX - 1, INT_MIN + 1),
		Vector2ll(INT_MAX - 1, INT_MAX - 1)
	);

	LOG(triangle);

	LOG(sign(incircle(triangle, Vector2ll(INT_MAX, INT_MAX))));
	LOG(sign(incircle(triangle, Vector2ll(0, 0))));
	LOG(sign(incircle(triangle, Vector2ll(INT_MIN, INT_MAX))));
	LOG(sign(incircle(triangle, Vector2ll(0, 1))));
	*/

	ftec::DesktopEngine::create<ftec::Razura>();

	WAIT();
	return 0;
}

