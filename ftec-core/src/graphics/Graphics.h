#pragma once

#include <vector>
#include <memory>

#include "Layer.h"								//For LAYER_ALL

namespace ftec {

	//Special forward declares
	template <typename T> struct Vector4;	typedef Vector4<unsigned char>	Color32;
	template <typename T> struct Matrix4;	typedef Matrix4<float>			Matrix4f;

	template <typename T> struct line3;		typedef line3<float>			line3f;
	template <typename T> struct triangle3; typedef triangle3<float>		triangle3f;
	template <typename T> struct sphere;	typedef sphere<float>			spheref;
	template <typename T> struct Vector3;	typedef Vector3<float>			Vector3f;

	//Normal forward declares
	class SpriteBatch;
	class Mesh;
	class Camera;
	class Light;

	class InstanceList;

	struct Material;
	struct Material2D;

	//Stuff that should not be used outside the graphics stuff
	struct EnqueuedMesh;
	template <typename T> struct ColorType;
	
	class Graphics {
	private:

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
		static void enqueueMesh(const Mesh *mesh, const Material *material, const Matrix4f &modelMatrix, Layer layer = LAYER_ALL, InstanceList* list = nullptr);

		//Enqueues the mesh for rendering
		static void enqueueLine(const line3f &line, const Color32 &color);

		//Enqueues the mesh for rendering
		static void enqueuePoint(const Vector3f &point, const Color32 &color);

		//Enqueues the mesh for rendering
		static void enqueueTriangle(const triangle3f &triangle, const Color32 &color);

		//Enqueues the mesh for rendering
		static void enqueueSphere(const spheref &sphere, const Color32 &color);

		//Enqueues the camera to render the scene
		static void enqueueCamera(const Camera *camera);

		//Enqueues the camera to render the scene
		static void enqueueLight(const Light *light);

		//Ends drawing, performs all draw calls and stuff
		static void end();
	};
}