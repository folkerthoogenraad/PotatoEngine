#include "Graphics.h"

#include "GL.h"
#include "logger/log.h"
#include "Renderer.h"
#include "engine/Engine.h"
#include "GraphicsState.h"
#include "Cubemap.h"

#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"

#include "Layer.h"

#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "math/Line3.h"
#include "math/Triangle3.h"
#include "math/Sphere.h"
#include "math/Vector4.h"

#include "SpriteBatch.h"

//This should not be here, because this is a graphics stuff
#include "resources/ResourceManager.h"

#define DEBUG_GRAPHICS 0


namespace ftec {

	struct EnqueuedMesh {
		const Mesh *mesh;
		const Material *material;

		Matrix4f modelMatrix;
		Layer layer;

		const InstanceList *list;
	};

	template <typename T> struct ColorType {
		T mesh;
		Color32 color;
	};

	std::vector<EnqueuedMesh> Graphics::meshes = {};
	std::vector<const Camera *> Graphics::cameras = {};
	std::vector<const Light *> Graphics::lights = {};
	bool Graphics::drawing = false;

	std::unique_ptr<SpriteBatch> Graphics::renderer;
	std::shared_ptr<Material2D> Graphics::pointMaterial;
	std::vector<ColorType<Line3f>> Graphics::lines;
	std::vector<ColorType<Vector3f>> Graphics::points;
	std::vector<ColorType<Spheref>> Graphics::spheres;
	std::vector<ColorType<Triangle3f>> Graphics::triangles;

	void Graphics::begin()
	{
		if (drawing) {
			LOG_ERROR("Cant start drawing while drawing");
			return;
		}
		drawing = true;

		if (!renderer) {
			renderer = std::make_unique<SpriteBatch>();
		}
		if (!pointMaterial) {
			pointMaterial = std::make_shared<Material2D>();
			pointMaterial->m_TextureMap = Engine::getResourceManager().load<Texture>(DEFAULT_TEXTURE_WHITE);
			pointMaterial->m_Shader = Engine::getResourceManager().load<Shader>("shaders/default2d");
		}

		meshes.clear();
		cameras.clear();
		lights.clear();
		lines.clear();
		points.clear();
		triangles.clear();
		spheres.clear();
		
	}
	//TODO constness and stuff
	void Graphics::enqueueMesh(const Mesh *mesh, const Material *material, const Matrix4f &modelMatrix, Layer layer, const InstanceList *list)
	{
		meshes.push_back({
			mesh, material, modelMatrix, layer, list
		});
	}

	void Graphics::enqueueLine(const Line3f & line, const Color32 &color)
	{
		lines.push_back({line, color });
	}

	void Graphics::enqueuePoint(const Vector3f & point, const Color32 &color)
	{
		points.push_back({point, color });
	}

	void Graphics::enqueueTriangle(const Triangle3f & triangle, const Color32 &color)
	{
		triangles.push_back({ triangle, color });
	}

	void Graphics::enqueueSphere(const Spheref & sphere, const Color32 & color)
	{
		spheres.push_back({ sphere, color });
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

				Renderer::renderport(Rectanglei(0, 0, l->getShadowBuffer()->getWidth(), l->getShadowBuffer()->getHeight()));

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				Matrix4f projection =  l->getShadowMatrix();

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

			//Set skybox to normal version //This should obviously not be here
			GraphicsState::m_Skybox = Engine::getResourceManager().load<Cubemap>("textures/skybox/test");
			
			GraphicsState::matrixModel = Matrix4f::translation(c->m_Position);

			//Drawing skybox
			GraphicsState::m_Lights[0].enabled = false; //Idk man

			PBRMaterial skyboxMaterial(nullptr, Engine::getResourceManager().load<Shader>("shaders/skybox"));

			GraphicsState::m_Material = &skyboxMaterial;
			auto mesh = Engine::getResourceManager().load<Mesh>("mesh/skybox.obj");


			Renderer::drawDirect(*mesh);

			glClear(GL_DEPTH_BUFFER_BIT);
			

			GraphicsState::m_Lights[0].enabled = true;
			GraphicsState::m_Lights[0].light = *lights.front();// .m_DiRectangleion = Vector3f(0.7f, -0.4f, -0.7f).normalize();


			for (auto m : meshes) {
				//TODO material sorting
				//TODO batching

				//Only draw when layer masks align
				if ((m.layer & c->m_LayerMask) != 0) {

					GraphicsState::matrixModel = m.modelMatrix;
					GraphicsState::m_Material = m.material;
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
					if (m.list) {
						Renderer::drawDirect(*m.mesh, *m.list);
					}
					else {
						Renderer::drawDirect(*m.mesh);
					}
				}
			}
			
			GraphicsState::m_Material = pointMaterial.get();
			GraphicsState::m_Skybox = nullptr;
			GraphicsState::matrixModel = Matrix4f::identity();

			glPointSize(5);
			glLineWidth(1);

			renderer->begin(Primitive::POINTS);
			renderer->color(Color32::white());
			for (auto &p : points) {
				renderer->color(p.color);
				renderer->vertex(p.mesh);
			}
			renderer->end();

			renderer->begin(Primitive::LINES);
			renderer->color(Color32::white());
			for (auto &l : lines) {
				renderer->color(l.color);
				renderer->vertex(l.mesh.a);
				renderer->vertex(l.mesh.b);
			}
			renderer->end();

			renderer->begin(Primitive::TRIANGLES);
			for (auto &t : triangles) {
				renderer->color(t.color);
				renderer->vertex(t.mesh.a);
				renderer->vertex(t.mesh.b);
				renderer->vertex(t.mesh.c);
			}
			renderer->end();

			auto sphere = Engine::getResourceManager().load<Mesh>("mesh/sphere.obj");

			for (auto &s : spheres) {
				GraphicsState::matrixModel = Matrix4f::translation(s.mesh.center) * Matrix4f::scale(Vector3f(s.mesh.radius, s.mesh.radius, s.mesh.radius));
				Renderer::drawDirect(*sphere);
			}
		}

	}
}
