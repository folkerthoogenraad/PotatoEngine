#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "logger/log.h"
#include "graphics/Window.h"
#include "graphics/SpriteBatch.h"
#include "math/mat4.h"
#include "resources/ResourceManager.h"
#include "graphics/Renderer.h"
#include "scene/Scene.h"
#include "graphics/Material.h"

int main(void)
{
	using namespace ftec;

	//Initialize GLFW
	if (!glfwInit()) {
		TERMINATE("Failed to initialize GLFW");
	}

	//Create window and OpenGL context on current thread
	Window window("PotatoEngine", 1024, 768);

	//Initialize extentions
	if (glewInit() != GLEW_OK) {
		TERMINATE("Couldn't init glew!");
	}

	//Tell the world how great we are
	LOG("Libraries loaded.");
	LOG("OpenGL" << glGetString(GL_VERSION));

	auto texture = ResourceManager::getDefault().load<Texture>("textures/spritesheet");
	auto shader = ResourceManager::getDefault().load<Shader>("shaders/default");

	Material material(texture, shader);
	Camera camera(90.f,16.f/6.f,.1f,1000.f);
	vec3 position;
	Renderer renderer;
	VBORenderable renderable(3);

	renderable.m_Vertices[0].position = vec3(0, 0, 0);
	renderable.m_Vertices[1].position = vec3(0, 0, 0);
	renderable.m_Vertices[2].position = vec3(0, 0, 0);

	renderable.update(0, 3);

	//Start running the shit out of this game
	while (!window.isCloseRequested()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.draw(renderable, material, camera, position);

		window.update();
	}


	glfwTerminate();

	return 0;
}