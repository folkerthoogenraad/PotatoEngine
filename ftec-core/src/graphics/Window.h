#pragma once

#include <string>

struct GLFWwindow;

namespace ftec {

	class Window {
		int m_Width, m_Height;
		std::string m_Name;

		GLFWwindow *m_Window;

		double m_MouseX, m_MouseY;

		int m_MSAA;
		bool m_Fullscreen;
		bool m_CloseRequested;
		bool m_Resized;
		bool m_vSync;
	public:
		Window(std::string name, int width, int height, bool full = false, bool vsync = true, int msaa = 0);
		~Window();
		void update();

		void poll();
		void swap();

		void setCursorMode(int mode);
		void setVisible(bool visible);

		inline float getAspectRatio() { return getWidth() / getHeight(); }
		inline float getWidth() { return (float)m_Width; }
		inline float getHeight() { return (float)m_Height; }

		void setMousePosition(double xpos, double ypos);

		inline bool isCloseRequested() const { return m_CloseRequested; }
		inline bool isResized() const { return m_Resized; }

		//Callbacks
		friend void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void type_callback(GLFWwindow* window, unsigned int unicode);
		friend void resize_callback(GLFWwindow* window, int width, int height);
		friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	private:
		void init();
	};
}
