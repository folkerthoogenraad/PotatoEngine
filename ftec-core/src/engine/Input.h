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
		static std::set<int> typedKeys;
		static std::string keystring;

		static std::set<int> downMouse;
		static std::set<int> pressedMouse;
		static std::set<int> releasedMouse;

		static vec2f mousePosition;
		static vec2f mouseDelta;
		static vec2f scrollDelta;

		static int cursorMode;
		static bool disabled;
	public:
		static bool isKeyDown(int keycode);
		static bool isKeyPressed(int keycode);
		static bool isKeyReleased(int keycode);
		static bool isKeyTyped(int keycode);

		static bool isMouseButtonDown(int keycode);
		static bool isMouseButtonPressed(int keycode);
		static bool isMouseButtonReleased(int keycode);

		static float getMouseX();
		static float getMouseY();
		static float getMouseDX();
		static float getMouseDY();

		static vec2f getMousePosition();
		static vec2f getMouseDelta();
		static vec2f getScroll();

		static void setCursorMode(int mode);
		static void reset();

		static inline void setEnabled(bool e) { disabled = !e; };
		static inline bool isEnabled() { return disabled; };

		static const std::string &getKeyString() { return keystring; }

		static const std::set<int> &getKeysDown() { return downKeys; }
		static const std::set<int> &getKeysPressed() { return pressedKeys; }
		static const std::set<int> &getKeysReleased() { return releasedKeys; }
		static const std::set<int> &getKeysTyped() { return typedKeys; }

		static const std::set<int> &getMouseButtonsDown() { return downMouse; }
		static const std::set<int> &getMouseButtonsPressed() { return pressedMouse; }
		static const std::set<int> &getMouseButtonsReleased() { return releasedMouse; }

		static void handleKey(int key, int scancode, int action, int mods);
		static void handleCursor(float x, float y);
		static void handleScroll(float x, float y);
		static void handleTyped(unsigned int unicode);
		static void handleMouse(int button, int action, int mods);
	};
}