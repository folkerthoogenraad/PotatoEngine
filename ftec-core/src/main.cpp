#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Window.h"
#include "logger/log.h"

#define EXIT() std::cin.get(); return -1;

int main(void)
{
	using namespace ftec;

	//Initialize GLFW
	if (!glfwInit()) {
		LOG_ERROR("Failed to initialize GLFW");
		EXIT();
	}

	//Create window and OpenGL context on current thread
	Window window("Sicke dodges boi", 1024, 768);

	//Initialize extentions
	if (glewInit() != GLEW_OK) {
		LOG_ERROR("Couldn't init glew!");
		EXIT();
	}

	//Tell the world how great we are
	LOG("Libraries loaded.");
	LOG("OpenGL" << glGetString(GL_VERSION));

	GLuint vbo;
	glGenBuffers(1, &vbo);

	//Start running the shit out of this game
	while (!window.isCloseRequested()){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.update();
	}


	glfwTerminate();

	return 0;
}