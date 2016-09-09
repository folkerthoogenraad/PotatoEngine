#include "Window.h"
#include "logger/log.h"

namespace ftec {
	Window::Window(std::string name, int width, int height)
		:m_Width(width), m_Height(height), m_Name(name)
	{
		init();
	}

	Window::~Window()
	{

	}

	void Window::update()
	{
		glfwPollEvents();
		m_CloseRequested = glfwWindowShouldClose(m_Window);
		glfwSwapBuffers(m_Window);
	}
	
	//The cursor position callback
	void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos)
	{
		Window *wp = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		if (wp) {
			Window &window = *wp;
			window.m_MousePosition = vec2(xpos, ypos);
		}
	}

	void Window::init()
	{
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
		if (!m_Window)
		{
			//TODO throw error
			LOG_ERROR("Failed to create window");
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSwapInterval(1);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	}
}
