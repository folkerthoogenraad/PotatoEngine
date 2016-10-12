#pragma once

#include <fstream>
#include "XMLDocument.h"

namespace ftec {
	namespace xml {
		class XMLToken {
		public:
			enum Type {
				TEXT, OPENING, CLOSING
			}; // TODO attributes, 
			Type m_Type;
			std::string m_Text;
		};
		
		class XMLLexer {
			std::ifstream m_Stream;
			char m_Current;
		public:
			XMLLexer(const std::string &file);

			bool next(XMLToken &token);
			bool isEOF();
		};

		class XMLReader {
			XMLLexer m_Lexer;
		public:
			XMLReader(const std::string &file) : m_Lexer(file) {};
		};
	}
}