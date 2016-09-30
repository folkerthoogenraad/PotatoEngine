#pragma once

#include <string>
#include "math/helpers.h"

namespace potato {

	//Edit text must have features:
	// - Multiline support (Somehow)
	// - List of allowed characters
	// - Backspace and delete clustering
	// - crtl + backspace/delete for words
	// - Mouse selections?!?!
	// - Custom word delimiters

	struct EditText {
		enum DeletionStrategy {
			CHARACTER,
			WORD,
			LINE
		};
		enum Direction {
			FORWARD,
			BACKWARD,
		};
		std::string m_Text = "";

		//Selection start and end can have negative width!
		int m_SelectionStart = 0;
		int m_SelectionEnd = 0;
		int m_CursorPosition = 0;		//It is named a carret, not a cursor ):

		void clamp();
		inline size_t length() { return m_Text.length(); }
		inline size_t selectionStart() { return ftec::min(m_SelectionStart, m_SelectionEnd); }
		inline size_t selectionEnd() { return ftec::max(m_SelectionStart, m_SelectionEnd); }
		inline size_t selectionSize() { return ftec::distance(m_SelectionStart, m_SelectionEnd); }

		//Selection stuff
		void moveCursor(size_t newPos, bool makeSelection);

		void insertAtCursor(const std::string &data);
		void deleteAtCursor(Direction dir, DeletionStrategy strat);

		std::string getSelectedText();

		void cancelSelection();
		void deleteSelection();

		void keyboardInput();
	};


	//Static helper stuff
	//TODO change this name

}