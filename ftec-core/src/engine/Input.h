#pragma once
#include "math/vec2.h"
#include <set>
#include <string>
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
		static std::string typedKeys;

		static vec2f mousePosition;
		static vec2f mouseDelta;
	public:
		static bool isKeyDown(int keycode);
		static bool isKeyPressed(int keycode);
		static bool isKeyReleased(int keycode);

		static float getMouseX();
		static float getMouseY();
		static float getMouseDX();
		static float getMouseDY();

		static vec2f getMousePosition();
		static vec2f getMouseDelta();

		static const std::string &getTypedKeys() { return typedKeys; }

		static void setCursorMode(int mode);
		static void reset();

		static void handleKeyTyped(unsigned int typed);
		static void handleKey(int key, int scancode, int action, int mods);
		static void handleCursor(float x, float y);
	};
}