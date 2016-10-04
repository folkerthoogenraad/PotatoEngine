#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "math/math.h"
#include "Renderer.h"
#include "Light.h"

namespace ftec {
	
	class Graphics {

	private:
		struct EnqueuedMesh {
			EnqueuedMesh(const Mesh *m, const Material *mat, const mat4 &model, Layer layer, InstanceList *list)
				:mesh(m), material(mat), modelMatrix(model), layer(layer), list(list){};
			const Mesh *mesh;
			const Material *material;
			mat4 modelMatrix;
			Layer layer;
			InstanceList *list;
		};

		static std::vector<EnqueuedMesh> meshes;
		static std::vector<const Camera*> cameras;
		static std::vector<const Light*> lights;
		static bool drawing;

	public:
		//Begins drawing, clears all buffers
		static void begin();

		//Enqueues the mesh for rendering
		static void enqueueMesh(const Mesh *mesh, const Material *material, const mat4 &modelMatrix = mat4::identity(), Layer layer = LAYER_ALL, InstanceList* list = nullptr);

		//Enqueues the camera to render the scene
		static void enqueueCamera(const Camera *camera);

		//Enqueues the camera to render the scene
		static void enqueueLight(const Light *light); //Loss of constness because setting light position, should be different probably

		//Ends drawing, performs all draw calls and stuff
		static void end();
	};
}