
#include "engine/Engine.h"

#include "logger/log.h"
#include "graphics/Window.h"
#include "graphics/SpriteBatch.h"
#include "math/mat4.h"
#include "resources/ResourceManager.h"
#include "graphics/Renderer.h"
#include "scene/Scene.h"
#include "graphics/Material.h"
#include "io/ioutils.h"

#include "engine/Game.h"

using namespace ftec;

class DefaultGame : public Game {
public:

	Camera cam;
	std::shared_ptr<Mesh> mesh;
	Material mat;

	DefaultGame() : mat(0, 0) {

	}

	void init() override {
		auto texture = Engine::getResourceManager().load<Texture>("textures/table_texture.png");
		auto shader = Engine::getResourceManager().load<Shader>("shaders/default");
		mesh = Engine::getResourceManager().load<Mesh>("mesh/test.obj");

		mat = Material(texture, shader);
		cam = Camera(60, 4.f / 3.f, .1f, 1000.f);
		cam.m_Position.y = 1.7f;
	}

	void update() override {

	}

	void render() override {
		Renderer::draw(*mesh, mat, cam, mat4::translation(vec3(0, 0, -5)) * mat4::rotation(5, vec3(0, 1, 0)));
		Renderer::draw(*mesh, mat, cam, mat4::translation(vec3(3, 0, -4)) * mat4::rotation(10, vec3(0, 1, 0)));
		Renderer::draw(*mesh, mat, cam, mat4::translation(vec3(-3.5, 0, -4.5)) * mat4::rotation(-5, vec3(0, 1, 0)));
		Renderer::draw(*mesh, mat, cam, mat4::translation(vec3(0.5, 0, -8)) * mat4::rotation(15, vec3(0, 1, 0)));
	}

	void destroy() override {

	}
};

int main(void)
{	
	Engine::create(std::make_unique<DefaultGame>());

	std::cin.get();

	return 0;
}

