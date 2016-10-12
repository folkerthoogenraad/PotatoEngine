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
		bool XMLLexer::next(XMLToken & token)
		{
			if (isEOF())
				return false;

			if (m_Current == '<') {
				std::stringstream data;

				m_Stream.get(m_Current);
				if (m_Current == '/') {
					token.m_Type = XMLToken::CLOSING;
					m_Stream.get(m_Current);
				}
				else {
					token.m_Type = XMLToken::OPENING;
				}

				while (m_Current != '>' && !isEOF()) {
					data << m_Current;

					m_Stream.get(m_Current);
				}
				//consume the <
				m_Stream.get(m_Current);

				token.m_Text = data.str();

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
					token.m_Type = XMLToken::TEXT;
					token.m_Text = data.str();
					return true;
				}
				else {
					return next(token);
				}

			}
		}
		bool XMLLexer::isEOF()
		{
			return m_Stream.eof();
		}
	}
}
