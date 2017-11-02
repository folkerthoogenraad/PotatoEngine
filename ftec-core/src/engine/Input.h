#pragma once

#include <set>
#include <string>
#include <vector>
#include "math/Vector2.h"

#include "Keycodes.h" //This is not needed, but its just better for everyone that uses input anyway. Will remove later on, probalby

namespace ftec {

	template <typename T>
	struct Vector2;
	typedef Vector2<float> Vector2f;

	enum class CursorMode {
		NORMAL, HIDDEN, GRABBED
	};

	struct TypeInput {
		int keycode;
		int unicode;
	};

	class Input {
#if 0
		std::set<int> downKeys = std::set<int>();
		std::set<int> pressedKeys = std::set<int>();
		std::set<int> releasedKeys = std::set<int>();

		std::vector<TypeInput> typedKeys = std::vector<TypeInput>();

		std::set<int> downMouse = std::set<int>();
		std::set<int> pressedMouse = std::set<int>();
		std::set<int> releasedMouse = std::set<int>();

		CursorMode cursorMode = CursorMode::NORMAL;
		bool disabled = false;

		std::string keystring = "";
		Vector2f mousePosition = Vector2f();
		Vector2f mouseDelta = Vector2f();
		Vector2f scrollDelta = Vector2f();

		std::array<Vector2f, 20> mousePressPositions;
#endif
	public:
		Input() = delete;

		static bool isKeyDown(int keycode);
		static bool isKeyPressed(int keycode);
		static bool isKeyReleased(int keycode);
		static bool isKeyTyped(int keycode);

		static bool isMouseButtonDown(int keycode);
		static bool isMouseButtonPressed(int keycode);
		static bool isMouseButtonReleased(int keycode);

		static Vector2f getMouseLastPressedPosition(int mousebutton);

		static float getMouseX();
		static float getMouseY();
		static float getMouseDX();
		static float getMouseDY();

		static Vector2f getMousePosition();
		static Vector2f getMouseDelta();
		static Vector2f getScroll();

		static void setCursorMode(CursorMode mode);
		static void reset();

		static void setEnabled(bool e);
		static bool isEnabled();

		static const std::string &getKeyString();

		static const std::set<int> &getKeysDown();
		static const std::set<int> &getKeysPressed();
		static const std::set<int> &getKeysReleased();
		static const std::vector<TypeInput> &getKeysTyped();

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