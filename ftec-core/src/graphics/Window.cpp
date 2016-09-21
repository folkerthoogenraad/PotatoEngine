#include "Window.h"
#include "logger/log.h"
#include "engine/Input.h"

namespace ftec {
	Window::Window(std::string name, int width, int height, bool fullscreen)
		:m_Width(width), m_Height(height), m_Name(name), m_Fullscreen(fullscreen)
	{
		init();
	}

	Window::~Window()
	{

	}

	void Window::update()
	{
		poll();
		swap();
	}

	void Window::poll()
	{
		glfwPollEvents();
		m_CloseRequested = glfwWindowShouldClose(m_Window);

		//TODO setup things for input stuff
	}

	void Window::setCursorMode(int mode)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, mode);
	}

	void Window::swap()
	{
		glfwSwapBuffers(m_Window);
	}


	void Window::init()
	{
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), m_Fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
		if (!m_Window)
		{
			//TODO throw error
			LOG_ERROR("Failed to create window");
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSwapInterval(1);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetKeyCallback(m_Window, key_callback);
	}

	//The cursor position callback
	void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos)
	{
		//TODO remove legacy
		Window *wp = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		if (wp) {
			Window &window = *wp;
			window.m_MousePosition = vec2f(xpos, ypos);
		}
		Input::handleCursor((float)xpos, (float)ypos);
	}


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input::handleKey(key, scancode, action, mods);
	}
}
