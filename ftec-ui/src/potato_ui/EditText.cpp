#include "EditText.h"
#include "engine/Input.h"
#include "logger/log.h"

#include "PotatoUI.h"
#include "engine/Keycodes.h"

namespace potato {

	void EditText::normalize()
	{
		int l = (int) length();

		ftec::clamp(m_CursorPosition, 0, l);

		ftec::clamp(m_SelectionEnd, 0, l);
		ftec::clamp(m_SelectionStart, 0, l);
	}

	void EditText::setCursorPosition(size_t newPos, bool makeSelection)
	{
		m_CursorPosition = (int)newPos;
		if (!makeSelection) {
			cancelSelection();
		}
		else {
			m_SelectionEnd = m_CursorPosition;
		}
		normalize();
	}

	void EditText::moveCursor(Direction dir, Strategy strat, bool makeSelection)
	{
		m_CursorPosition = (int)getIndexFromCursor(dir,strat);
		if (!makeSelection) {
			cancelSelection();
		}
		else {
			m_SelectionEnd = m_CursorPosition;
		}
		normalize();
	}

	void EditText::insertAtCursor(const std::string & data)
	{
		deleteSelection();
		m_Text.insert(m_CursorPosition, data);
		setCursorPosition(m_CursorPosition + data.length(), false);

	}

	void EditText::deleteAtCursor(Direction dir, Strategy strat)
	{
		if (selectionSize() > 0) {
			deleteSelection();
			return;
		}
		int idx = getIndexFromCursor(dir, strat);

		int amount = ftec::distance(idx, m_CursorPosition);
		idx = ftec::min(idx, m_CursorPosition);

		if (amount <= 0)
			return;

		m_Text.erase(
			(size_t) idx,
			(size_t) amount
		);

		m_CursorPosition = idx;
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
		normalize();
		m_CursorPosition = (int)selectionStart();
		m_Text.erase(selectionStart(), selectionSize());
		cancelSelection();
		normalize();
	}

	int EditText::clamp(int index) const
	{
		return ftec::clamp(0, (int)m_Text.size(), index);
	}

	bool EditText::inbounds(int index) const
	{
		return !(index < 0 || index >= m_Text.size());
	}

	int EditText::getIndexFromCursor(Direction dir, Strategy strat)
	{
		if (m_Text.size() == 0)
			return 0;

		int direction = dir == Direction::FORWARD ? 1 : -1;

		if (strat == Strategy::CHARACTER) {
			return clamp(m_CursorPosition + direction);
		}
		else if (strat == Strategy::WORD) {
			int currentIndex = m_CursorPosition + direction; //Should this be added? Tune in next week to find out
			
			while (inbounds(currentIndex)) {
				if (isspace(m_Text[currentIndex]))
					break;
				currentIndex += direction;
			}

			return clamp(currentIndex);
		}
		else {
			return -1;
		}
		
		return 0;
	}

	void EditText::keyboardInput()
	{
		bool shiftDown = (ftec::Input::isKeyDown(KEY_LEFT_SHIFT) || ftec::Input::isKeyDown(KEY_RIGHT_SHIFT));
		bool crtlDown = (ftec::Input::isKeyDown(KEY_LEFT_CONTROL) || ftec::Input::isKeyDown(KEY_RIGHT_CONTROL));

		Strategy strat = crtlDown ? Strategy::WORD : Strategy::CHARACTER;

		//Move cursor
		if (ftec::Input::isKeyTyped(KEY_LEFT)) {
			moveCursor(Direction::BACKWARD, strat, shiftDown);
		}
		if (ftec::Input::isKeyTyped(KEY_RIGHT)) {
			moveCursor(Direction::FORWARD, strat, shiftDown);
		}
		if (ftec::Input::isKeyTyped(KEY_HOME)) {
			setCursorPosition(0, shiftDown);
		}
		if (ftec::Input::isKeyTyped(KEY_END)) {
			setCursorPosition(m_Text.length(), shiftDown);
		}

		//Input text
		if (ftec::Input::getKeyString().length() > 0) {
			insertAtCursor(ftec::Input::getKeyString());
		}

		//Backspace and delete
		if (ftec::Input::isKeyTyped(KEY_BACKSPACE)) {
			deleteAtCursor(BACKWARD, strat);
		}
		if (ftec::Input::isKeyTyped(KEY_DELETE)) {
			deleteAtCursor(FORWARD, strat);
		}

		//Helpful functionality
		if (crtlDown) {
			if (ftec::Input::isKeyPressed(KEY_A)) {
				m_SelectionStart = 0;
				m_SelectionEnd = (int)m_Text.length();
				m_CursorPosition = (int)m_Text.length();
			}

			if (ftec::Input::isKeyPressed(KEY_C)) {
				PotatoClipboard::setData(getSelectedText());
			}

			if (ftec::Input::isKeyPressed(KEY_X)) {
				PotatoClipboard::setData(getSelectedText());
				deleteSelection();
			}

			//crtl + v is a keytyped event
			if (ftec::Input::isKeyTyped(KEY_V)) {
				insertAtCursor(PotatoClipboard::getData());
			}

		}
	}
}