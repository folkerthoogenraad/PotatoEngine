#include "Graphics.h"
#include "logger/log.h"
#include "Renderer.h"
#include "engine/Engine.h"

#define DEBUG_GRAPHICS 0

namespace ftec {

	std::vector<Graphics::EnqueuedMesh> Graphics::meshes = {};
	std::vector<const Camera *> Graphics::cameras = {};
	std::vector<const Light *> Graphics::lights = {};
	bool Graphics::drawing = false;

	//NOO DONT DO THJIS 
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;

	void Graphics::begin()
	{
		if (drawing) {
			LOG_ERROR("Cant start drawing while drawing");
			return;
		}
		drawing = true;

		meshes.clear();
		cameras.clear();
		lights.clear();
		
		if (!mesh) { //TODO not do this here.
			mesh = std::make_shared<Mesh>();
			mesh->m_Vertices = {
				vec3f(-1,-1),
				vec3f(1,-1),
				vec3f(1,1),
				vec3f(-1,1)
			};
			mesh->m_Normals = { vec3f(0,0,1), vec3f(0,0,1), vec3f(0,0,1), vec3f(0,0,1) };
			mesh->m_Uvs = {
				vec2f(0,0),
				vec2f(1,0),
				vec2f(1,1),
				vec2f(0,1)
			};
			mesh->m_Triangles = {
				0, 1, 2,
				0, 2, 3
			};

			mesh->upload();

			material = std::make_shared<Material>();

			material->m_Shader = Engine::getResourceManager().load<Shader>("shaders/passthrough");
		}
	}

	void Graphics::enqueueMesh(const Mesh *mesh, const Material *material, const mat4 &modelMatrix, Layer layer)
	{
		meshes.push_back({
			mesh, material, modelMatrix, layer
		});
	}

	void Graphics::enqueueCamera(const Camera *camera)
	{
		cameras.push_back(camera);
	}

	void Graphics::enqueueLight(const Light * light)
	{
		lights.push_back(light);
	}

	void Graphics::end()
	{
		if (!drawing) {
			LOG_ERROR("Can't stop drawing while not drawing");
			return;
		}

		drawing = false;

		if (cameras.size() < 1)
			return;//If there are no camera's, we might as well just stop drawing.

		//Draw for every light
		for (auto l : lights) {

			//Only if it has shadows enabled ofc, else it is just silly
			if (l->isShadowsEnabled()) {
				l->getShadowBuffer()->bind();

				Renderer::renderport(rect2i(0, 0, l->getShadowBuffer()->getWidth(), l->getShadowBuffer()->getHeight()));

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				mat4 projection =  l->getShadowMatrix();

				for (auto m : meshes) {

					//TODO layer masks with ignore shadows
					Renderer::drawDirect(*m.mesh, *m.material, Light::defaultLight(), projection, mat4::identity(), m.modelMatrix);


				}


				l->getShadowBuffer()->unbind();

#if DEBUG_GRAPHICS
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				Renderer::renderport(0, 0, Engine::getWindow().getWidth(), Engine::getWindow().getHeight());

				material->m_Texture = l->getShadowBuffer()->getDepthTexture();

				Renderer::drawDirect(*mesh, *material, Light::defaultLight() , mat4::identity(), mat4::identity(), mat4::identity());
#endif
			}
		}

#if DEBUG_GRAPHICS
		if (true)
			return;
#endif

		//Draw for every camera
		for (auto c : cameras) {
			//TODO material overwrite?

			//Set the correct render target, if the camera has a custom render target
			if (c->hasRenderTarget()) {
				c->m_RenderTarget->bind();
				Renderer::renderport(rect2i(0, 0, c->m_RenderTarget->getWidth(), c->m_RenderTarget->getHeight()));
			}

			//TODO do this only if the camera requests this
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			
			const Light *l = nullptr;
			if (lights.size() > 0)
				l = lights.front();

			for (auto m : meshes) {
				//TODO material sorting
				//TODO batching

				//Only draw when layer masks align
				if((m.layer & c->m_LayerMask) != 0)
					Renderer::drawDirect(*m.mesh, *m.material, l == nullptr ? Light::defaultLight() : *l, *c, m.modelMatrix);
			}

			//Reset the render target, if the camera has no render target any more
			if (c->hasRenderTarget()) {
				c->m_RenderTarget->unbind();

				if (c->m_RenderToScreen) {
					//TODO dont do it like this probably
					Renderer::renderport(rect2i(0, 0, (int) Engine::getWindow().getWidth(), (int) Engine::getWindow().getHeight()));
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


					material->m_Texture = c->m_RenderTarget->getTexture();
					auto oldShader = material->m_Shader;

					if (c->m_PostProcessingShader)
						material->m_Shader = c->m_PostProcessingShader;

					Renderer::drawDirect(*mesh, *material, l == nullptr ? Light::defaultLight() : *l, mat4::identity(), mat4::identity(), mat4::identity());
				
					if (c->m_PostProcessingShader)
						material->m_Shader = oldShader;
				}
			}

		}

	}
}
