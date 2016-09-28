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
		bool m_Resized;
	public:
		Window(std::string name, int width, int height, bool full);
		~Window();
		void update();

		void poll();
		void swap();

		void setCursorMode(int mode);
		void setVisible(bool visible);

		inline float getWidth() { return (float)m_Width; }
		inline float getHeight() { return (float)m_Height; }
		
		inline vec2f getMousePosition() const { return m_MousePosition; }
		inline bool isCloseRequested() const { return m_CloseRequested; }
		inline bool isResized() const { return m_Resized; }

		friend void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void type_callback(GLFWwindow* window, unsigned int unicode);
		friend void resize_callback(GLFWwindow* window, int width, int height);
	private:
		void init();
	};
}
