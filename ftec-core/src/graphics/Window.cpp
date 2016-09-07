#include "Window.h"
#include "logger/log.h"

ftec::Window::Window(std::string name, int width, int height)
	:m_Width(width), m_Height(height), m_Name(name)
{
	init();
}

ftec::Window::~Window()
{

}

void ftec::Window::update()
{
	glfwPollEvents();
	m_CloseRequested = glfwWindowShouldClose(m_Window);
	glfwSwapBuffers(m_Window);
}
void ftec::Window::init()
{
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
	if (!m_Window)
	{
		//TODO throw error
		LOG_ERROR("Failed to create window");
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
}

