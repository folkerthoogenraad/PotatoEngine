#pragma once
#include "math/vec2.h"
#include <set>
#include "graphics/GL.h"

#define CURSOR_NORMAL GLFW_CURSOR_NORMAL
#define CURSOR_HIDDEN GLFW_CURSOR_HIDDEN
#define CURSOR_GRABBED GLFW_CURSOR_DISABLED

namespace ftec {
	class Input {
	protected:
		static std::set<int> downKeys;
		static std::set<int> pressedKeys;
		static std::set<int> releasedKeys;

		static vec2 mousePosition;
		static vec2 mouseDelta;
	public:
		static bool isKeyDown(int keycode);
		static bool isKeyPressed(int keycode);
		static bool isKeyReleased(int keycode);

		static float getMouseX();
		static float getMouseY();
		static float getMouseDX();
		static float getMouseDY();

		static vec2 getMousePosition();
		static vec2 getMouseDelta();

		static void setCursorMode(int mode);
		static void reset();

		static void handleKey(int key, int scancode, int action, int mods);
		static void handleCursor(float x, float y);
	};
}