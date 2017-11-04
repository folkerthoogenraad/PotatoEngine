#pragma once

#include <string>
#include <vector>

#include "engine/Event.h"


struct GLFWwindow;

namespace ftec {

	class Window {
	protected:
		int m_Width, m_Height;
		std::string m_Name;

		int m_MSAA;
		bool m_Fullscreen;
		bool m_CloseRequested;
		bool m_Resized;
		bool m_vSync;

	public:
		Window(std::string name, int width, int height, bool full = false, bool vsync = true, int msaa = 0);
		virtual ~Window() = default;

		virtual void poll(std::vector<Event> &events) = 0;
		virtual void swap() = 0;

		virtual void setVisible(bool visible) = 0;

		inline float getAspectRatio() { return getWidth() / getHeight(); }
		inline float getWidth() { return (float)m_Width; }
		inline float getHeight() { return (float)m_Height; }

		inline bool isCloseRequested() const { return m_CloseRequested; }
		inline bool isResized() const { return m_Resized; }

	};


	
}
