#pragma once

#include "GL.h"

#include <string>
#include "math/math.h"

namespace ftec {
	class Window {
		int m_Width, m_Height;
		std::string m_Name;

		GLFWwindow *m_Window;

		vec2f m_MousePosition;
		bool m_Fullscreen;
		bool m_CloseRequested;
	public:
		Window(std::string name, int width, int height, bool full);
		~Window();
		void update();

		void poll();
		void swap();

		void setCursorMode(int mode);

		inline float getWidth() { return (float)m_Width; }
		inline float getHeight() { return (float)m_Height; }
		
		inline vec2f getMousePosition() const { return m_MousePosition; }
		inline bool isCloseRequested() const { return m_CloseRequested; }
		friend void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	private:
		void init();
	};
	void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}
