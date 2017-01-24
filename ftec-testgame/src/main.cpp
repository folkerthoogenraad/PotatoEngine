#include "game/Razura.h"
#include "engine/DesktopEngine.h"

#include "logger/log.h"

#include "math/Rational.h"
#include "math/Vector2.h"
#include "math/Matrix2.h"


int main(void)
{
	using namespace ftec;

	//ftec::DesktopEngine::create<ftec::Razura>();

	Matrix2<rational> matrix({
		1,2,
		3,4
	});

	LOG(matrix.determinant());
	
	WAIT();

	return 0;
}

