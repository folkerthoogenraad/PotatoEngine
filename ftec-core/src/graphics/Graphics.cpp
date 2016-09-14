#include "Graphics.h"
#include "logger/log.h"
#include "Renderer.h"

namespace ftec {

	std::vector<Graphics::EnqueuedMesh> Graphics::meshes = {};
	std::vector<const Camera *> Graphics::cameras = {};
	bool Graphics::drawing = false;

	void Graphics::begin()
	{
		if (drawing) {
			LOG_ERROR("Cant start drawing while drawing");
			return;
		}
		drawing = true;

		meshes.clear();
		cameras.clear();
	}

	void Graphics::enqueueMesh(const Mesh *mesh, const Material *material, const mat4 &modelMatrix, int layer)
	{
		meshes.push_back({
			mesh, material, modelMatrix, layer
		});
	}

	void Graphics::enqueueCamera(const Camera & camera)
	{
		cameras.push_back(&camera);
	}

	void Graphics::end()
	{
		if (!drawing) {
			LOG_ERROR("Can't stop drawing while not drawing");
			return;
		}

		//TODO draw here
		for (auto c : cameras) {
			//TODO render target
			//TODO material overwrite?

			for (auto m : meshes) {
				//TODO material sorting
				//TODO batching

				//Only draw when layer masks align
				if((m.layer & c->m_LayerMask) != 0)
					Renderer::drawDirect(*m.mesh, *m.material, *c, m.modelMatrix);
			}
		}

		drawing = false;
	}
}
