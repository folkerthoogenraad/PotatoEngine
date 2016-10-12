#pragma once

#include <fstream>
#include <iostream>

#include "XMLDocument.h"

namespace ftec {
	namespace xml {
		class XMLToken {
		public:
			enum Type {
				TEXT, OPENING, CLOSING, SELFCLOSING
			}; // TODO attributes, 
			Type m_Type;
			std::string m_Text;

			friend std::ostream &operator<<(std::ostream &stream, XMLToken& token);
		};
		
		class XMLLexer {
			std::ifstream m_Stream;
			XMLToken m_CurrentToken;
			char m_Current;
		public:
			XMLLexer(const std::string &file);

			XMLToken &current() { return m_CurrentToken; }

			bool next();
			bool isEOF();
		};

		bool read(const std::string &file, XMLDocument &out);
		bool read(XMLLexer &reader, XMLNode &out);
	}
}