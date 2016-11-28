#include "game/Razura.h"
#include "engine/Engine.h"

#include "logger/log.h"

#include "math/mat3.h"
#include "math/vec2.h"

int main(void)
{
	using namespace ftec;

	mat3f mat = mat3f().translate(2, 3).scale(4, 4).translate(1, 1);

	vec2f p(1, 1);

	LOG(mat * p);

	//ftec::Engine::create<ftec::Razura>();

	WAIT();

	return 0;
}

