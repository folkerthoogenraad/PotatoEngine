#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "math/Rational.h"
#include "math/Vector2.h"


int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	Vector2<rational> vec;

	LOG(vec);
	WAIT();

	return 0;
}

