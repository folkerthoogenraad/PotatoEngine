#include "EditText.h"
#include "engine/Input.h"
#include "logger/log.h"

#include "PotatoUI.h"

namespace potato {

	void EditText::clamp()
	{
		int l = length();

		ftec::clamp(m_CursorPosition, 0, l);

		ftec::clamp(m_SelectionEnd, 0, l);
		ftec::clamp(m_SelectionStart, 0, l);
	}

	void EditText::moveCursor(size_t newPos, bool makeSelection)
	{
		m_CursorPosition = newPos;
		if (!makeSelection) {
			cancelSelection();
		}
		else {
			m_SelectionEnd = m_CursorPosition;
		}
		clamp();
	}

	void EditText::insertAtCursor(const std::string & data)
	{
		deleteSelection();
		m_Text.insert(m_CursorPosition, data);
		moveCursor(m_CursorPosition + data.length(), false);

	}

	void EditText::deleteAtCursor(Direction dir, DeletionStrategy strat)
	{
		if (selectionSize() > 0) {
			deleteSelection();
			return;
		}
		
		if (strat == CHARACTER) {
			if (dir == BACKWARD && m_CursorPosition > 0) {
				m_Text.erase(m_CursorPosition - 1, (size_t)1);
				moveCursor(m_CursorPosition - 1, false);
			}
			else if (dir == FORWARD && m_Text.length() > 0) {
				m_Text.erase(m_CursorPosition, (size_t)1);
			}
		}
		if (strat == WORD) {
			int d = dir == FORWARD ? 1 : -1;
			//The carret position is AFTER the character, so depending on the offset we start removing from the current carret position or one below that
			int offset = dir == BACKWARD ? -1 : 0;

			int startIndex = m_CursorPosition + offset;
			int endIndex = startIndex;

			//We must first find a character, and then we can start removeing the word
			bool charFound = false;

			for (; endIndex >= 0 && endIndex < m_Text.length(); endIndex += d) {
				if (!charFound) {
					if (!isspace(m_Text[endIndex])) {
						charFound = true;
					}
				}
				else {
					if (isspace(m_Text[endIndex])) {
						break;
					}
				}
			}

			if (ftec::distance(startIndex, endIndex) > 0) {
				//And here we subtract that offset again
				m_Text.erase((size_t)ftec::min(startIndex, endIndex) - offset, (size_t)ftec::distance(startIndex, endIndex));
				moveCursor(ftec::min(startIndex, endIndex) - offset, false);
			}
		}
		if (strat == LINE) {

		}
	}

	std::string EditText::getSelectedText()
	{
		return m_Text.substr(selectionStart(), selectionSize());
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
		m_CursorPosition = selectionStart();
		m_Text.erase(selectionStart(), selectionSize());
		cancelSelection();
		clamp();
	}


	void EditText::keyboardInput()
	{
		bool shiftDown = (ftec::Input::isKeyDown(GLFW_KEY_LEFT_SHIFT) || ftec::Input::isKeyDown(GLFW_KEY_RIGHT_SHIFT));
		bool crtlDown = (ftec::Input::isKeyDown(GLFW_KEY_LEFT_CONTROL) || ftec::Input::isKeyDown(GLFW_KEY_RIGHT_CONTROL));

		//Move cursor
		if (ftec::Input::isKeyTyped(GLFW_KEY_LEFT)) {
			moveCursor(m_CursorPosition - 1, shiftDown);
		}
		if (ftec::Input::isKeyTyped(GLFW_KEY_RIGHT)) {
			moveCursor(m_CursorPosition + 1, shiftDown);
		}
		if (ftec::Input::isKeyTyped(GLFW_KEY_HOME)) {
			moveCursor(0, shiftDown);
		}
		if (ftec::Input::isKeyTyped(GLFW_KEY_END)) {
			moveCursor(m_Text.length(), shiftDown);
		}

		//Input text
		if (ftec::Input::getKeyString().length() > 0) {
			insertAtCursor(ftec::Input::getKeyString());
		}

		//Backspace and delete
		DeletionStrategy strat = crtlDown ? DeletionStrategy::WORD : DeletionStrategy::CHARACTER;
		if (ftec::Input::isKeyTyped(GLFW_KEY_BACKSPACE)) {
			deleteAtCursor(BACKWARD, strat);
		}
		if (ftec::Input::isKeyTyped(GLFW_KEY_DELETE)) {
			deleteAtCursor(FORWARD, strat);
		}

		//Helpful functionality
		if (crtlDown) {
			if (ftec::Input::isKeyPressed(GLFW_KEY_A)) {
				m_SelectionStart = 0;
				m_SelectionEnd = m_Text.length();
				m_CursorPosition = m_Text.length();
			}

			if (ftec::Input::isKeyPressed(GLFW_KEY_C)) {
				PotatoClipboard::setData(getSelectedText());
			}

			if (ftec::Input::isKeyPressed(GLFW_KEY_X)) {
				PotatoClipboard::setData(getSelectedText());
				deleteSelection();
			}

			//crtl + v is a keytyped event
			if (ftec::Input::isKeyTyped(GLFW_KEY_V)) {
				insertAtCursor(PotatoClipboard::getData());
			}

		}
	}
}