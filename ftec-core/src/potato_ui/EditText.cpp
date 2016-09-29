#include "EditText.h"
#include "engine/Input.h"
#include "logger/log.h"

namespace potato {

	void EditText::clamp()
	{
		int l = length();

		ftec::clamp(m_CursorPosition, 0, l);

		ftec::clamp(m_SelectionEnd, 0, l);
		ftec::clamp(m_SelectionStart, 0, l);
	}

	void EditText::moveCursor(size_t newPos)
	{
		m_CursorPosition = newPos;
		if (!(ftec::Input::isKeyDown(GLFW_KEY_LEFT_SHIFT) || ftec::Input::isKeyDown(GLFW_KEY_RIGHT_SHIFT))) {
			cancelSelection();
		}
		else {
			m_SelectionEnd = m_CursorPosition;
		}
		clamp();
	}

	void EditText::cancelSelection()
	{
		m_SelectionStart = m_CursorPosition;
		m_SelectionEnd = m_CursorPosition;
	}

	void EditText::deleteSelection()
	{
		if (selectionSize() < 1)
			return;

		//Just to be sure
		clamp();
		m_Text.erase(selectionStart(), selectionSize());
		cancelSelection();
		clamp();
	}


	void EditText::parseInput()
	{
		if (ftec::Input::isKeyTyped(GLFW_KEY_LEFT)) {
			moveCursor(m_CursorPosition - 1);
		}
		if (ftec::Input::isKeyTyped(GLFW_KEY_RIGHT)) {
			moveCursor(m_CursorPosition + 1);
		}
		if (ftec::Input::isKeyTyped(GLFW_KEY_HOME)) {
			moveCursor(0);
		}
		if (ftec::Input::isKeyTyped(GLFW_KEY_END)) {
			moveCursor(m_Text.length());
		}

		size_t keys = ftec::Input::getKeyString().length();

		if (keys > 0) {
			deleteSelection();

			m_Text.insert(m_CursorPosition, ftec::Input::getKeyString());

			m_CursorPosition += keys;
			cancelSelection();
		}

		//TODO cluster backspace and delete
		if (ftec::Input::isKeyTyped(GLFW_KEY_BACKSPACE)) {
			if (selectionSize() > 0) {
				deleteSelection();
			}
			else {
				if (m_CursorPosition > 0) {
					m_Text.erase(m_CursorPosition - 1, (size_t)1);
					moveCursor(m_CursorPosition - 1);
				}
			}
		}

		if (ftec::Input::isKeyTyped(GLFW_KEY_DELETE)) {
			if (selectionSize() > 0) {
				deleteSelection();
			}
			else {
				if (m_Text.length() > 0) {
					m_Text.erase(m_CursorPosition, (size_t) 1);
					moveCursor(m_CursorPosition);
				}
			}
		}

	}
}