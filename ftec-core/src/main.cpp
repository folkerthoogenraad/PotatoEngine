#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "logger/log.h"
#include "graphics/Window.h"
#include "graphics/SpriteBatch.h"
#include "math/mat4.h"
#include "resources/ResourceManager.h"
#include "scene/Scene.h"
#include "graphics/Texture.h"

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

	SpriteBatch batch;

	//Start running the shit out of this game
	while (!window.isCloseRequested()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene::getCurrent().update();

		window.update();
	}


	glfwTerminate();

	return 0;
}