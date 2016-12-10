#pragma once

//TODO remove most of all these things
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"

#include "Layer.h"

#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "math/line3.h"
#include "math/triangle3.h"
#include "math/sphere.h"
#include "math/Vector4.h"

#include "SpriteBatch.h"
#include <memory>

namespace ftec {

	class SpriteBatch;
	
	class Graphics {

	private:
		struct EnqueuedMesh {
			const Mesh *mesh;
			const Material *material;

			Matrix4f modelMatrix;
			Layer layer;

			InstanceList *list;
		};

		template <typename T>
		struct ColorType {
			T mesh;
			Color32 color;
		};

		static std::unique_ptr<SpriteBatch> renderer;

		//TODO all these things should be rendered correctly, and efficiently, which they currently don't
		static std::vector<ColorType<line3f>> lines;
		static std::vector<ColorType<Vector3f>> points;
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
		static void enqueueMesh(const Mesh *mesh, const Material *material, const Matrix4f &modelMatrix = Matrix4f::identity(), Layer layer = LAYER_ALL, InstanceList* list = nullptr);

		//Enqueues the mesh for rendering
		static void enqueueLine(const line3f &line, const Color32 &color = Color32::white());

		//Enqueues the mesh for rendering
		static void enqueuePoint(const Vector3f &point, const Color32 &color = Color32::white());

		//Enqueues the mesh for rendering
		static void enqueueTriangle(const triangle3f &triangle, const Color32 &color = Color32::white());

		//Enqueues the mesh for rendering
		static void enqueueSphere(const spheref &sphere, const Color32 &color = Color32::white());

		//Enqueues the camera to render the scene
		static void enqueueCamera(const Camera *camera);

		//Enqueues the camera to render the scene
		static void enqueueLight(const Light *light);

		//Ends drawing, performs all draw calls and stuff
		static void end();
	};
}