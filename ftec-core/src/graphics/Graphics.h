#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "math/math.h"

namespace ftec {
	
	class Graphics {

	private:
		struct EnqueuedMesh {
			EnqueuedMesh(const Mesh *m, const Material *mat, const mat4 &model, int layer)
				:mesh(m), material(mat), modelMatrix(model), layer(layer){};
			const Mesh *mesh;
			const Material *material;
			mat4 modelMatrix;
			int layer;
		};

		static std::vector<EnqueuedMesh> meshes;
		static std::vector<const Camera*> cameras;
		static bool drawing;

	public:
		//Begins drawing, clears all buffers
		static void begin();

		//Enqueues the mesh for rendering
		static void enqueueMesh(const Mesh *mesh, const Material *material, const mat4 &modelMatrix = mat4::identity(), int layer = LAYER_ALL);

		//Enqueues the camera to render the scene
		static void enqueueCamera(const Camera &camera);

		//Ends drawing, performs all draw calls and stuff
		static void end();
	};
}