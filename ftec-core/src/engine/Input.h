#pragma once

#include <set>
#include <string>

namespace ftec {

	template <typename T>
	struct vec2;
	typedef vec2<float> vec2f;

	enum class CursorMode {
		NORMAL, HIDDEN, GRABBED
	};

	class Input {
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

		static void setCursorMode(CursorMode mode);
		static void reset();

		static void setEnabled(bool e);
		static bool isEnabled();

		static const std::string &getKeyString();

		static const std::set<int> &getKeysDown();
		static const std::set<int> &getKeysPressed();
		static const std::set<int> &getKeysReleased();
		static const std::set<int> &getKeysTyped();

		static const std::set<int> &getMouseButtonsDown();
		static const std::set<int> &getMouseButtonsPressed();
		static const std::set<int> &getMouseButtonsReleased();

		static void handleKey(int key, int scancode, int action, int mods);
		static void handleCursor(float x, float y);
		static void handleScroll(float x, float y);
		static void handleTyped(unsigned int unicode);
		static void handleMouse(int button, int action, int mods);
	};
}