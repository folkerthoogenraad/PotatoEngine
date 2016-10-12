#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"
#include "io/XMLReader.h"

int main(void)
{
	using namespace ftec;
	using namespace xml;

	XMLLexer lexer("text.xml");

	XMLToken token;

	while (lexer.next(token)) {
		LOG(token.m_Type << " " << token.m_Text);
	}

	WAIT();
	if (true)
		return 0;

	ftec::Engine::create<ftec::Razura>();
	return 0;
}

