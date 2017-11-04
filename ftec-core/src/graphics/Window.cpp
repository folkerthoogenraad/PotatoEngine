#include "Window.h"

namespace ftec {
	
	Window::Window(std::string name, int width, int height, bool full, bool vsync, int msaa)
		:m_Width(width), m_Height(height), m_Name(name), m_Fullscreen(full), m_MSAA(msaa), m_vSync(vsync)
	{
	}
}
