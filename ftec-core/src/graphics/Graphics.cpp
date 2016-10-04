#include "Graphics.h"
#include "logger/log.h"
#include "Renderer.h"
#include "engine/Engine.h"
#include "GraphicsState.h"
#include "Cubemap.h"

#define DEBUG_GRAPHICS 0

namespace ftec {

	std::vector<Graphics::EnqueuedMesh> Graphics::meshes = {};
	std::vector<const Camera *> Graphics::cameras = {};
	std::vector<const Light *> Graphics::lights = {};
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
		lights.clear();
		
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
			/*if (l->isShadowsEnabled()) {
				l->getShadowBuffer()->bind();

				Renderer::renderport(rect2i(0, 0, l->getShadowBuffer()->getWidth(), l->getShadowBuffer()->getHeight()));

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				mat4 projection =  l->getShadowMatrix();

				for (auto m : meshes) {

					//TODO layer masks with ignore shadows
					//TODO draw shadows per camera and not per global.
					//TODO make a different render pass for this, instead of using this draw direct stuff
					//TODO render the objects for the shadowmaps
				}


				l->getShadowBuffer()->unbind();

			}*/
		}

		//Draw for every camera
		for (auto c : cameras) {
			//TODO material overwrite?

			//TODO Set the correct render target, if the camera has a custom render target

			//TODO do this only if the camera requests this
			glClear(GL_DEPTH_BUFFER_BIT);

			GraphicsState::eyePosition = c->m_Position;
			GraphicsState::matrixProjection = c->getProjectionMatrix();
			GraphicsState::matrixView = c->getViewMatrix();

			GraphicsState::matrixModel = mat4::translation(c->m_Position);

			//Set skybox to normal version
			GraphicsState::m_Skybox = Engine::getResourceManager().load<Cubemap>("textures/skybox/test");

			//Drawing skybox
			
			GraphicsState::m_Material = Material(nullptr, Engine::getResourceManager().load<Shader>("shaders/skybox"));
			auto mesh = Engine::getResourceManager().load<Mesh>("mesh/skybox.obj");

			GraphicsState::m_TextureEnabled = false;
			GraphicsState::m_LightEnabled = false;

			Renderer::drawDirect(*mesh);

			glClear(GL_DEPTH_BUFFER_BIT);

			GraphicsState::m_LightEnabled = true;

			GraphicsState::m_Lights[0].enabled = true;
			GraphicsState::m_Lights[0].light = *lights.front();// .m_Direction = vec3f(0.7f, -0.4f, -0.7f).normalize();

			GraphicsState::m_TextureEnabled = true;

			for (auto m : meshes) {
				//TODO material sorting
				//TODO batching

				//Only draw when layer masks align
				if ((m.layer & c->m_LayerMask) != 0) {

					GraphicsState::matrixModel = m.modelMatrix;
					GraphicsState::m_Material = *m.material;
					/*
					GraphicsState::m_Shader = m.material->m_Shader;

					GraphicsState::m_Textures[0].enabled = true;
					GraphicsState::m_Textures[0].texture = m.material->m_TextureMap;
					//TODO just give the graphicsstate a material
					if (m.material->m_NormalMap) {
						GraphicsState::m_Textures[1].enabled = true;
						GraphicsState::m_Textures[1].texture = m.material->m_NormalMap;
					}
					else {
						GraphicsState::m_Textures[1].enabled = false;
					}*/

					Renderer::drawDirect(*m.mesh);
				}
			}

		}

	}
}
