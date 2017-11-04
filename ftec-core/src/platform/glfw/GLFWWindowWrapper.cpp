#include "GLFWWindowWrapper.h"

#include "graphics/GL.h"
#include "GLFW/glfw3.h"

#include "logger/log.h"
#include "engine/Input.h"

#include <assert.h>

namespace ftec {

	GLFWWindowWrapper::GLFWWindowWrapper(std::string name, int width, int height, bool fullscreen, bool vsync, int msaa)
		: Window(name, width, height, fullscreen, vsync, msaa)
	{
		init();
	}

	GLFWWindowWrapper::~GLFWWindowWrapper()
	{

	}

	void GLFWWindowWrapper::poll(std::vector<Event> &events)
	{
		m_Resized = false;
		m_Events.clear();

		glfwPollEvents();

		// TODO return the events as a thing now.

		events = m_Events;

		m_CloseRequested = glfwWindowShouldClose(m_Window) > 0;
	}

	void GLFWWindowWrapper::setCursorMode(int mode)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, mode);
	}

	void GLFWWindowWrapper::swap()
	{
		glfwSwapBuffers(m_Window);
	}

	void GLFWWindowWrapper::setVisible(bool visible)
	{
		if (visible) {
			glfwShowWindow(m_Window);
		}
		else {
			glfwHideWindow(m_Window);
		}
	}

	void GLFWWindowWrapper::setMousePosition(Vector2f position)
	{
		m_MousePosition = position;

		glfwSetCursorPos(m_Window, position.x, position.y);
	}


	void GLFWWindowWrapper::init()
	{
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_SAMPLES, m_MSAA);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), m_Fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
		if (!m_Window)
		{
			//TODO throw error
			LOG_ERROR("Failed to create window");
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSwapInterval(m_vSync ? 1 : 0);

		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetWindowSizeCallback(m_Window, resize_callback);
		glfwSetCharCallback(m_Window, type_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
	}

	//The cursor position callback
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		GLFWWindowWrapper *wp = static_cast<GLFWWindowWrapper*>(glfwGetWindowUserPointer(window));
		assert(wp->validMagic());
		Event e = wp->createDefaultEvent();

		Vector2f position = Vector2f((float)xpos, (float)ypos);

		wp->m_MouseDelta = position - wp->m_MousePosition;
		wp->m_MousePosition = position;

		e.m_MouseDelta = wp->m_MouseDelta;
		e.m_MousePosition = wp->m_MousePosition;

		if (wp->m_MouseDown.size() == 0) {
			e.m_EventType = EventType::MOUSE_MOVE;

			wp->m_Events.push_back(e);
		}
		else {
			e.m_EventType = EventType::MOUSE_DRAG;
			for (auto i : wp->m_MouseDown) {
				e.m_MouseButton = i;
				wp->m_Events.push_back(e);
			}
		}
	}


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		GLFWWindowWrapper *wp = static_cast<GLFWWindowWrapper*>(glfwGetWindowUserPointer(window));
		assert(wp->validMagic());

		Event e = wp->createDefaultEvent();
		e.m_KeyCode = key;

		if (action == GLFW_PRESS) {
			wp->m_KeyDown.insert(key);
			e.m_EventType = EventType::KEYBOARD_PRESSED;
			wp->m_Events.push_back(e);
		}
		if (action == GLFW_RELEASE) {
			wp->m_KeyDown.erase(key);
			e.m_EventType = EventType::KEYBOARD_RELEASED;
			wp->m_Events.push_back(e);
		}

	}

	void type_callback(GLFWwindow * window, unsigned int unicode)
	{
		GLFWWindowWrapper *wp = static_cast<GLFWWindowWrapper*>(glfwGetWindowUserPointer(window));
		assert(wp->validMagic());

		Event e = wp->createDefaultEvent();

		e.m_EventType = EventType::KEYBOARD_TYPED;
		e.m_UnicodeKey = unicode;

		wp->m_Events.push_back(e);
	}
	void resize_callback(GLFWwindow * window, int width, int height)
	{
		GLFWWindowWrapper *wp = static_cast<GLFWWindowWrapper*>(glfwGetWindowUserPointer(window));
		assert(wp->validMagic());

		if (wp) {
			wp->m_Resized = true;
			wp->m_Width = width;
			wp->m_Height = height;
		}
	}

	void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
	{
		GLFWWindowWrapper *wp = static_cast<GLFWWindowWrapper*>(glfwGetWindowUserPointer(window));
		assert(wp->validMagic());

		Event e = wp->createDefaultEvent();

		e.m_EventType = EventType::MOUSE_SCROLL;
		e.m_ScrollDirection.x = (float)xoffset;
		e.m_ScrollDirection.y = (float)yoffset;

		wp->m_Events.push_back(e);
	}


	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		GLFWWindowWrapper *wp = static_cast<GLFWWindowWrapper*>(glfwGetWindowUserPointer(window));
		assert(wp->validMagic());

		Event e = wp->createDefaultEvent();

		if (action == GLFW_PRESS) {
			wp->m_MouseDown.insert(button);
			e.m_EventType = EventType::MOUSE_PRESSED;
		}
		if (action == GLFW_RELEASE) {
			wp->m_MouseDown.erase(button);
			e.m_EventType = EventType::MOUSE_RELEASED;
		}

		e.m_MouseButton = button;

		wp->m_Events.push_back(e);
	}

	Event GLFWWindowWrapper::createDefaultEvent()
	{
		Event event;

		event.m_MousePosition = m_MousePosition;
		event.m_MouseDelta = m_MouseDelta;

		event.m_AltDown = false;
		event.m_CrtlDown = false;
		event.m_ShiftDown = false;

		return event;
	}
}