#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"
#include "io/XMLReader.h"

#include "math/collision.h"
#include "math/mat3.h"

#include "math/DelaunayVertex.h"

#include "math/triangle3.h"
#include "math/plane.h"
#include "math/lego3.h"
#include "math/Delaunay3D.h"

int main(void)
{
	using namespace ftec;

	ftec::Engine::create<ftec::Razura>();

	WAIT();
	return 0;
}

