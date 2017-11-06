#pragma once

#include "graphics/Window.h"

#include <set>
#include <array>

struct GLFWwindow;

namespace ftec {
	class GLFWWindowWrapper : public Window {
		GLFWwindow *m_Window;

		// Stuff we need for handling events and creating the event list
		std::set<int> m_KeyDown;
		std::set<int> m_MouseDown;

		std::array<Vector2f, 0x0F> m_MouseStartPosition;
		Vector2f m_MousePosition;
		Vector2f m_MouseDelta;

		std::vector<Event> m_Events;

		unsigned int m_Magic = 0x1A2B3C4D;
	public:
		GLFWWindowWrapper(std::string name, int width, int height, bool full = false, bool vsync = true, int msaa = 0);
		~GLFWWindowWrapper();

		void poll(std::vector<Event> &events) override;
		void swap() override;

		void setCursorMode(int mode);
		void setVisible(bool visible) override;

		void setMousePosition(Vector2f position);

		// To check if the pointer is valid.
		inline bool validMagic() const { return m_Magic == 0x1A2B3C4D; }

		//Callbacks
		friend void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void type_callback(GLFWwindow* window, unsigned int unicode);
		friend void resize_callback(GLFWwindow* window, int width, int height);
		friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	private:
		Event createDefaultEvent();
		void init();
	};
}