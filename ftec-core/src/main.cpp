#define GLEW_STATIC
#define FREEIMAGE_LIB

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FreeImage.h"

#include "logger/log.h"
#include "graphics/Window.h"
#include "graphics/SpriteBatch.h"
#include "math/mat4.h"
#include "resources/ResourceManager.h"
#include "graphics/Renderer.h"
#include "scene/Scene.h"
#include "graphics/Material.h"
#include "io/ioutils.h"

void initGL();

int main(void)
{
	using namespace ftec;

	//Initialize GLFW
	if (!glfwInit()) {
		TERMINATE("Failed to initialize GLFW");
	}

	//Create window and OpenGL context on current thread
	Window window("PotatoEngine", 800, 600, false);

	//Initialize extentions
	if (glewInit() != GLEW_OK) {
		TERMINATE("Couldn't init glew!");
	}

	FreeImage_Initialise();

	initGL();

	//Tell the world how great we are
	LOG("Libraries loaded.");
	LOG("OpenGL" << glGetString(GL_VERSION));

	auto texture = ResourceManager::getDefault().load<Texture>("textures/wheelchair_texture.png");
	auto shader = ResourceManager::getDefault().load<Shader>("shaders/default");
	auto mesh = ResourceManager::getDefault().load<Mesh>("mesh/test.obj");

	Material mat(texture, shader);
	Camera cam(60, 4.f / 3.f, .1f, 1000.f);

	float f = 0;

	vec2 previousMousePosition = window.getMousePosition();

	//Start running the shit out of this game
	while (!window.isCloseRequested()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vec2 newMousePosition = window.getMousePosition();
		vec2 delta = newMousePosition - previousMousePosition;
		previousMousePosition = newMousePosition;

		cam.m_Yaw += delta.x / 50.f;
		cam.m_Pitch += delta.y / 50.f;

		if (cam.m_Pitch > 30) cam.m_Pitch = 30;
		if (cam.m_Pitch < -30) cam.m_Pitch = -30;
		if (cam.m_Yaw > 30) cam.m_Yaw = 30;
		if (cam.m_Yaw < -30) cam.m_Yaw = -30;

		const float distance = -5;

		f += 1.f;

		Renderer::draw(*mesh, mat, cam, mat4::translation(vec3(0, -1.7f, distance)) * mat4::rotation(f, vec3(0, 1, 0)));

		window.update();
	}

	FreeImage_DeInitialise();
	glfwTerminate();

	return 0;
}

void initGL() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glClearColor(.2f, .4f, 8.f, 1.f);
}