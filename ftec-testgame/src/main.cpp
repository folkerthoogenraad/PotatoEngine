#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "math/Rational.h"
#include "math/Vector2.h"
#include "math/Matrix4.h"


int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	Matrix4<rational> matrix({
		1,2,3,4,
		12,13,14,15,
		4,5,6,1,
		4,8,1,3
	});

	LOG(matrix.determinant());
	
	WAIT();

	return 0;
}

