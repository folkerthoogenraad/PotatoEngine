#pragma once

#include <string>
#include <vector>

#include "engine/Event.h"

namespace ftec {
	/**
	 * The window base class for all implementation windowing.
	 * The window creates an OpenGL context automatically. After calling setVisible(true) you can start rendering with OpenGL. 
	 * @see EngineContext
	*/
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

		/**
		 * Polls the events for the current window and puts the result in the argument
		 * @param events The output list of events
		*/
		virtual void poll(std::vector<Event> &events) = 0;

		/**
		 * Swaps the back and the front buffer
		*/
		virtual void swap() = 0;

		virtual void setVisible(bool visible) = 0;

		inline float getAspectRatio() { return getWidth() / getHeight(); }
		inline float getWidth() { return (float)m_Width; }
		inline float getHeight() { return (float)m_Height; }

		/**
		 * Returns whether the user pressed the close button on the window. The return value is only changed after each call to poll()
		 * @see poll()
		 * @return Is the close requested
		*/
		inline bool isCloseRequested() const { return m_CloseRequested; }

		/**
		* Returns whether the user resized the window. The return value is only changed after each call to poll()
		* @see poll()
		* @return Window is resized
		*/
		inline bool isResized() const { return m_Resized; }

	};


	
}
