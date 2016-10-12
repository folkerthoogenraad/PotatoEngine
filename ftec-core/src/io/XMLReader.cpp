#include "XMLReader.h"

#include "logger/log.h"
#include <sstream>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

//Source: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring?page=1&tab=votes#tab-top
//TODO move this somehwere useful
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

namespace ftec {
	namespace xml {
		XMLLexer::XMLLexer(const std::string & file)
			: m_Stream(file)
		{
			m_Stream.get(m_Current);
		}
		bool XMLLexer::next()
		{
			if (isEOF())
				return false;

			if (m_Current == '<') {
				std::stringstream data;

				m_Stream.get(m_Current);
				if (m_Current == '/') {
					m_CurrentToken.m_Type = XMLToken::CLOSING;
					m_Stream.get(m_Current);
				}
				else {
					m_CurrentToken.m_Type = XMLToken::OPENING;
				}

				char previous = ' ';

				while (m_Current != '>' && !isEOF()) {
					if (previous == '/')
						data << previous;

					if(m_Current != '/')
						data << m_Current;

					previous = m_Current;
					m_Stream.get(m_Current);
				}
				//consume the <
				m_Stream.get(m_Current);

				if (previous == '/')
					m_CurrentToken.m_Type = XMLToken::SELFCLOSING;

				m_CurrentToken.m_Text = data.str();

				return true;
			}
			else {
				std::stringstream data;

				//TODO whitespace trimming

				while (m_Current != '>' && m_Current != '<' && !isEOF()) {
					data << m_Current;

					m_Stream.get(m_Current);
				}

				std::string text = data.str();
				trim(text);

				if (text.length() > 0) {
					m_CurrentToken.m_Type = XMLToken::TEXT;
					m_CurrentToken.m_Text = data.str();
					return true;
				}
				else {
					return next();
				}

			}
		}
		bool XMLLexer::isEOF()
		{
			return m_Stream.eof();
		}

		std::ostream &operator<<(std::ostream &stream, XMLToken& token)
		{
			switch (token.m_Type) {
			case XMLToken::OPENING:
				stream << "OPENING - ";
				break;
			case XMLToken::CLOSING:
				stream << "CLOSING - ";
				break;
			case XMLToken::TEXT:
				stream << "TEXT - ";
				break;
			case XMLToken::SELFCLOSING:
				stream << "SELFCLOSING - ";
				break;
			}

			return stream << token.m_Text;
		}


		bool read(const std::string &file, XMLDocument &document)
		{//TODO better error messaging
			XMLLexer lexer(file);

			if (!lexer.next())
				return false;

			if (!read(lexer, document.m_Root)) {
				return false;
			}

			return true;
		}

		bool read(XMLLexer &lexer, XMLNode &out)
		{ 
			//TODO better error messaging
			if (lexer.current().m_Type != XMLToken::OPENING && lexer.current().m_Type != XMLToken::SELFCLOSING)
				return false;
			
			std::stringstream input(lexer.current().m_Text);
			
			//Read the name as first attribute
			//This needs to be a bit cleaned up, but whatever
			std::string name;
			if (input >> name) {
				out.setTag(name);

				//To continue, we need to split stuff
				std::stringstream stream;
				char c;

				auto flush = [&]() {
					std::string result = stream.str();

					if (result.size() == 0)
						return;

					size_t index = result.find('=');

					if (index == std::string::npos) {
						out.setAttribute(result, "");
					}
					else {
						std::string attrib = result.substr(0, index);
						std::string value = result.substr(index + 2, result.size() - index - 3);

						out.setAttribute(attrib, value);
					}

					//clear the stringstream
					stream.str("");
				};

				while (input.get(c)) {
					if (std::isspace(c)) {
						flush();
					}
					else if (c == '"') {
						stream << c;

						while (input.get(c) && c != '"') {
							stream << c;
						}
						stream << c;
					}
					else if (c == '\'') {
						do stream << c;
						while (input.get(c) && c != '\'');
					}
					else {
						stream << c;
					}
				}
				flush();
			}
			else {
				return false;
			}

			if (lexer.current().m_Type == XMLToken::OPENING) {
				if (!lexer.next())
					return false;

				while (lexer.current().m_Type != XMLToken::CLOSING) {
					if (lexer.current().m_Type == XMLToken::TEXT) {
						std::string text = lexer.current().m_Text;
						trim(text);
						out.addText(text);

						if (!lexer.next())
							return false;
					}
					else if (lexer.current().m_Type == XMLToken::OPENING || lexer.current().m_Type == XMLToken::SELFCLOSING) {

						XMLNode child(XMLNode::Type::NODE);

						if (!read(lexer, child)) {
							return false;
						}

						out.addChild(child);
					}

				}
			}

			lexer.next();
			return true;
		}
	}
}
