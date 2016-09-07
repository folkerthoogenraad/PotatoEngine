#pragma once
#include <string>
#include <GLFW\glfw3.h>

namespace ftec {
	class Window {
		int m_Width, m_Height;
		std::string m_Name;

		GLFWwindow *m_Window;

		bool m_CloseRequested;
	public:
		Window(std::string name, int width, int height);
		~Window();
		void update();
		inline bool isCloseRequested() const { return m_CloseRequested; }
	private:
		void init();
	};
}