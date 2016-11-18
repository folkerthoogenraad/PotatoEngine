#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"

//TODO mat4 to mat4f, mat4i, mat4d
#include "math/mat4.h"
#include "math/vec3.h"
#include "math/line3.h"
#include "math/triangle3.h"
#include "math/sphere.h"

#include "SpriteBatch.h"
#include <memory>

namespace ftec {

	class SpriteBatch;
	
	class Graphics {

	private:
		struct EnqueuedMesh {
			/*EnqueuedMesh(const Mesh *m, const Material *mat, const mat4 &model, Layer layer, InstanceList *list)
				:mesh(m), material(mat), modelMatrix(model), layer(layer), list(list){};*/
			const Mesh *mesh;
			std::shared_ptr<Material> material;
			mat4 modelMatrix;
			Layer layer;
			InstanceList *list;
		};

		template <typename T>
		struct ColorType {
			T mesh;
			color32 color;
		};

		static std::unique_ptr<SpriteBatch> renderer;

		//TODO all these things should be rendered correctly, and efficiently, which they currently don't
		static std::vector<ColorType<line3f>> lines;
		static std::vector<ColorType<vec3f>> points;
		static std::vector<ColorType<triangle3f>> triangles;
		static std::vector<ColorType<spheref>> spheres;
		static std::shared_ptr<Material2D> pointMaterial;

		static std::vector<EnqueuedMesh> meshes;
		static std::vector<const Camera*> cameras;
		static std::vector<const Light*> lights;
		static bool drawing;

	public:
		//Begins drawing, clears all buffers
		static void begin();

		//Enqueues the mesh for rendering
		static void enqueueMesh(const Mesh *mesh, std::shared_ptr<Material> material, const mat4 &modelMatrix = mat4::identity(), Layer layer = LAYER_ALL, InstanceList* list = nullptr);

		//Enqueues the mesh for rendering
		static void enqueueLine(const line3f &line, const color32 &color = color32::white());

		//Enqueues the mesh for rendering
		static void enqueuePoint(const vec3f &point, const color32 &color = color32::white());

		//Enqueues the mesh for rendering
		static void enqueueTriangle(const triangle3f &triangle, const color32 &color = color32::white());

		//Enqueues the mesh for rendering
		static void enqueueSphere(const spheref &sphere, const color32 &color = color32::white());

		//Enqueues the camera to render the scene
		static void enqueueCamera(const Camera *camera);

		//Enqueues the camera to render the scene
		static void enqueueLight(const Light *light); //Loss of constness because setting light position, should be different probably

		//Ends drawing, performs all draw calls and stuff
		static void end();
	};
}