#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"
#include "io/XMLReader.h"

int main(void)
{
	using namespace ftec;
	using namespace xml;

	XMLDocument document;

	if (!read("text.xml", document))
		LOG("Failed to read document");



	LOG(document);

	WAIT();
	if (true)
		return 0;

	ftec::Engine::create<ftec::Razura>();
	return 0;
}

