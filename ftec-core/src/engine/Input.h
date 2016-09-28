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
		static std::string typedKeys;

		static vec2f mousePosition;
		static vec2f mouseDelta;
		static vec2f scrollDelta;
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
		static vec2f getScroll();

		static void setCursorMode(int mode);
		static void reset();

		static const std::string &getTypedKeys() { return typedKeys; }

		static const std::set<int> &getKeysDown() { return downKeys; }
		static const std::set<int> &getKeysPressed() { return releasedKeys; }
		static const std::set<int> &getKeysReleased() { return pressedKeys; }

		static void handleKey(int key, int scancode, int action, int mods);
		static void handleCursor(float x, float y);
		static void handleScroll(float x, float y);
		static void handleTyped(unsigned int unicode);
	};
}