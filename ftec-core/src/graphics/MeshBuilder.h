#pragma once

//All these includes are not needed
#include "math/Matrix4.h"

#include "Mesh.h"

namespace ftec {

	class MeshBuilder {
	public:
		static void addQuad(Mesh &mesh, const Matrix4f &center);
		static void addCube(Mesh &mesh, const Matrix4f &center);
	};

}