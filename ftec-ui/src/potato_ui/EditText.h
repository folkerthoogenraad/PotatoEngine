#pragma once

#include <string>
#include "math/math.h"

#include "engine/Event.h"

namespace potato {

	//Edit text must have features:
	// - Multiline support (Somehow)
	// - List of allowed characters
	// - Backspace and delete clustering
	// - crtl + backspace/delete for words
	// - Mouse selections?!?!
	// - Custom word delimiters

	struct EditText {

		enum Strategy {
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


		inline size_t length() { return m_Text.length(); }
		inline size_t selectionStart() { return ftec::min(m_SelectionStart, m_SelectionEnd); }
		inline size_t selectionEnd() { return ftec::max(m_SelectionStart, m_SelectionEnd); }
		inline size_t selectionSize() { return ftec::distance(m_SelectionStart, m_SelectionEnd); }

		void normalize();
		int clamp(int index) const;
		bool inbounds(int index) const;
		bool isSpace(int index) const;
		int getIndexFromCursor(Direction dir, Strategy strat);

		//Selection stuff
		void setCursorPosition(size_t newPos, bool makeSelection);
		void moveCursor(Direction dir, Strategy strat, bool makeSelection);

		void insertAtCursor(const std::string &data);
		void deleteAtCursor(Direction dir, Strategy strat);

		std::string getSelectedText();

		void cancelSelection();
		void deleteSelection();

		void keyboardInput(ftec::Event &evt);
	};


	//Static helper stuff
	//TODO change this name

}